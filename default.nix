{ lib
, stdenv
, cmake
}:

stdenv.mkDerivation rec {
  pname = "smalldeflate-cli";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [ cmake ];

  outputs = [ "out" "doc" "dev" ] ;

  buildPhase = "make -j $NIX_BUILD_CORES";
  installPhase = ''
        mkdir $out
        cp -r $TMP $out
          '';
  
  meta = with lib; {
    description    = "Command line interaction with sdefl.h and sinfl.h";
    homepage       = "https://github.com/bramtechs/smalldeflate-cli";
    license        = licenses.mit;
    maintainers    = with maintainers; [ bramtechs ];
    platforms      = platforms.all;
  };
}
