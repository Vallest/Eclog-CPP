empty: {}

object:
{
	empty: ""
	string: "Hello World!"
	string_2: "The quick brown fox jumps over the lazy dog."
	digits: "0123456789"
	symbols: "!@#$%^&*()_+-={}[]"
	utf8: "你好，世界！"
	escape: "\\\/\"\b\f\n\r\t"
	unicode_escape_4: "\u6587\u5B57"
	unicode_escape_v: "\u{a}\u{61}\u{1f60D}"
	surrogate: "\ud801\udC37\ud83c\uDf09"
}

config: {
	timeout: 90
	ip-address: "127.0.0.1"
	config.cipher: aes256-ctr
	_length_: 4096
}

