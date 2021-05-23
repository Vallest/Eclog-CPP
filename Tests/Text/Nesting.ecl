object:
{
	nested_object:
	{
		empty: ""
		string: "Hello World!"
		string_2: "The quick brown fox jumps over the lazy dog."
		digits: "0123456789"
		utf8: "你好，世界！"
	}

	nested_array: [
		inf
		nan
		3.14159265358979323846
		1e0
		1e100
	]

	nested_object2:
	{
		nested_array2:
		[
			{
				nested_array3:
				[
					"Hello World!"
					true
					1.0
					false
				]
			}
		]
	}
}

array:
[
	{
	}

	[
		null
		true
		false
		"Hello World!"
		3.14159265358979323846
		{}
		[]
		{
			timeout: 90
			ip-address: "127.0.0.1"
			config.cipher: aes256-ctr
			_length_: 4096
		}
	]

	{
		empty: @""
		string: @"Hello World!"
		utf8: @"你好，世界！"
	}
]
