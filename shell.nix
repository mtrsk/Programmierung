let
  pkgs = import ./pinned-nixpkgs.nix {};
  devTools = with pkgs; [
    ccls
  ];
in
(import ./default.nix {}).overrideAttrs (old: {
  buildInputs = old.buildInputs ++ devTools;
})
