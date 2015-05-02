{
  "targets": [
    {
      "target_name": "keybindings",
      "sources": ["src/keybindings.cpp"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    },
    {
      "target_name": "hello",
      "sources": ["src/hello.cc"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
