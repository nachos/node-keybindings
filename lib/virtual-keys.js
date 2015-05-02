'use strict';

var virtualKeys = [
  "Unused",
  "lmb",
  "rmb",
  "break",
  "mmb",
  "X1 mouse button",
  "X2 mouse button",
  "Undefined",
  "backspace",
  "tab",
  "Unknown",
  "Unknown",
  "clear",
  "enter",
  "Unknown",
  "Unknown",
  "shift",
  "ctrl",
  "alt",
  "pause",
  "capslock",
  "IME Kana mode",
  "Unknown",
  "IME Junja mode",
  "IME final mode",
  "IME Hanja mode",
  "Unknown",
  "esc",
  "IME convert",
  "IME nonconvert",
  "IME accept",
  "IME mode change",
  "space",
  "pageup",
  "pagedown",
  "end",
  "home",
  "left",
  "up",
  "right",
  "down",
  "select",
  "print",
  "execute",
  "printscreen",
  "insert",
  "delete",
  "help",
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "a",
  "b",
  "c",
  "d",
  "e",
  "f",
  "g",
  "h",
  "i",
  "j",
  "k",
  "l",
  "m",
  "n",
  "o",
  "p",
  "q",
  "r",
  "s",
  "t",
  "u",
  "v",
  "w",
  "x",
  "y",
  "z",
  "lwin",
  "rwin",
  "app",
  "Unknown",
  "sleep",
  "num0",
  "num1",
  "num2",
  "num3",
  "num4",
  "num5",
  "num6",
  "num7",
  "num8",
  "num9",
  "mul",
  "add",
  "separator",
  "sub",
  "decimal",
  "div",
  "f1",
  "f2",
  "f3",
  "f4",
  "f5",
  "f6",
  "f7",
  "f8",
  "f9",
  "f10",
  "f11",
  "f12",
  "f13",
  "f14",
  "f15",
  "f16",
  "f17",
  "f18",
  "f19",
  "f20",
  "f21",
  "f22",
  "f23",
  "f24",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "numlock",
  "scrolllock",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "lshift",
  "rshift",
  "lctrl",
  "rctrl",
  "lalt",
  "ralt",
  "browserback",
  "browserforward",
  "browserrefresh",
  "browserstop",
  "browsersearch",
  "browserfavorites",
  "browserhome",
  "volmute",
  "voldown",
  "volup",
  "nexttrack",
  "prevtrack",
  "stopmedia",
  "playpausemedia",
  "startmail",
  "selectmedia",
  "startapp1",
  "startapp2",
  "Unknown",
  "Unknown",
  ";:",
  "=+",
  ",<",
  "-_",
  ".>",
  "/?",
  "`~",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "[{",
  "\\|",
  "]}",
  "'\"",
  "OEM",
  "Unknown",
  "OEM",
  "<> or \\|",
  "OEM",
  "OEM",
  "IME Process key",
  "OEM",
  "VK_PACKET",
  "Unknown",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "OEM",
  "Attn",
  "CrSel",
  "ExSel",
  "Erase EOF",
  "play",
  "zoom",
  "Unknown",
  "PA1",
  "clear",
  "Unknown"
];

exports.getName = function (vkCode) {
  return virtualKeys[vkCode];
};

exports.getCode = function (vkString) {
  return virtualKeys.indexOf(vkString);
};