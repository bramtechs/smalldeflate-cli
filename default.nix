{
  pkgs ? import <nixpkgs> {}
}:

with pkgs;

pkgs.stdenv.mkDerivation {
  pname = "smalldeflate-cli";
  version = "0.0.5";

  src = ./.;

  nativeBuildInputs = [ cmake cxxopts ninja ];
  enableParallelBuilding = true;
  
  configurePhase = ''
    cmake . -G Ninja -DCMAKE_INSTALL_PREFIX=$out -DDONT_FETCH_PKGS=ON
  '';

  meta = with lib; {
    description    = "Command line interaction with sdefl.h and sinfl.h";
    homepage       = "https://github.com/bramtechs/smalldeflate-cli";
    license        = licenses.mit;
    maintainers    = with maintainers; [ bramtechs ];
    platforms      = platforms.all;
  };
}
