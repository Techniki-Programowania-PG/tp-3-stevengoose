{
  inputs = {
    utils.url = "github:numtide/flake-utils";
  };
  outputs =
    {
      self,
      nixpkgs,
      utils,
    }:
    utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShell =
          let
            python = pkgs.python313;
            pythonPackages = pkgs.python313Packages;
          in
          with pkgs;
          mkShell {
            buildInputs = [
              python
              pythonPackages.pybind11
              cmake
              gnuplot
            ];
            shellHook = ''
              SOURCE_DATE_EPOCH=$(date +%s)
              export CPATH=${python}/include/python3.13:$CPATH
              VENV=.venv

              if test ! -d $VENV; then
                python3.13 -m venv $VENV
              fi
              source ./$VENV/bin/activate
              export PYTHONPATH=`pwd`/$VENV/${python.sitePackages}/:$PYTHONPATH
              pip install -r requirements.txt
            '';
            postShellHook = ''
              ln -sf ${python.sitePackages}/* ./.venv/lib/python3.13/site-packages
            '';
          };
      }
    );
}
