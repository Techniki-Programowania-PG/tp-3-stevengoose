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
            python = pkgs.python312;
            pythonPackages = pkgs.python312Packages;
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
              export CPATH=${python}/include/python3.12:$CPATH
              VENV=.venv

              if test ! -d $VENV; then
                python3.12 -m venv $VENV
              fi
              source ./$VENV/bin/activate
              export PYTHONPATH=`pwd`/$VENV/${python.sitePackages}/:$PYTHONPATH
              pip install -r requirements.txt
            '';
            postShellHook = ''
              ln -sf ${python.sitePackages}/* ./.venv/lib/python3.12/site-packages
            '';
          };
      }
    );
}
