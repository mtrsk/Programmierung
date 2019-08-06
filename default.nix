{ pkgs ? import ./pinned-nixpkgs.nix {} }:

pkgs.stdenv.mkDerivation {
  name = "c-misc-project";
  buildInputs = with pkgs; [
    valgrind
    cmocka
  ];
}
