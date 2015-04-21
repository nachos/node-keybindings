{
  "targets": [
    {
      "target_name": "keybindings",
      "sources": ["src/keybindings.cpp"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
