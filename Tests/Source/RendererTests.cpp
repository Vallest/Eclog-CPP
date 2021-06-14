// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"

#include <Eclog/Renderer.h>
#include <Eclog/ObjectRenderer.h>
#include <Eclog/ArrayRenderer.h>
#include <Eclog/MemoryOutputStream.h>
#include <Eclog/StdStreamOutputStream.h>
#include <Eclog/Detail/Binary64.h>

#include <fstream>
#include <sstream>
#include <limits>

TEST_CASE("Renderer")
{
	SUBCASE("Empty")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "");
	}

	SUBCASE("Empty #2")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "");
	}

	SUBCASE("Empty #3")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc(eclog::RendererConfig::scheme_json_compatible);

		rc.formatting = eclog::RendererConfig::formatting_compact;

		eclog::Renderer renderer(stream, rc);

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "{}");
	}

	SUBCASE("Empty Key")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("", eclog::null);
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"\"\": null\n"
		);
	}

	SUBCASE("Null")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", eclog::null);
			root.renderMember("b", eclog::null);
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"a: null\n"
			"b: null\n"
		);
	}

	SUBCASE("Boolean")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", true);
			root.renderMember("b", false);
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"a: true\n"
			"b: false\n"
		);
	}

	SUBCASE("Quoted String")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("empty", eclog::StringDesc("", eclog::string_notation_quoted));
			root.renderMember("(string)", eclog::StringDesc("Hello World!", eclog::string_notation_quoted));
			root.renderMember("utf8", eclog::StringDesc("\xe4\xbd\xa0\xe5\xa5\xbd\xef\xbc\x8c\xe4\xb8\x96\xe7\x95\x8c\xef\xbc\x81", eclog::string_notation_quoted));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty: \"\"\n"
			"\"(string)\": \"Hello World!\"\n"
			"utf8: \"\xe4\xbd\xa0\xe5\xa5\xbd\xef\xbc\x8c\xe4\xb8\x96\xe7\x95\x8c\xef\xbc\x81\"\n"
		);
	}

	SUBCASE("Quoted String #2")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("escape", eclog::StringDesc(eclog::cstring("\\/\"\0\b\f\n\r\t", 9), eclog::string_notation_quoted));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"escape: \"\\\\/\\\"\\u0000\\b\\f\\n\\r\\t\"\n"
		);
	}

	SUBCASE("Unquoted String")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("empty", eclog::StringDesc("", eclog::string_notation_unquoted));
			root.renderMember("ctrl", eclog::StringDesc("\x1f", eclog::string_notation_unquoted));
			root.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_unquoted));
			root.renderMember("_host_", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
			root.renderMember("config.cipher", eclog::StringDesc("aes256-ctr", eclog::string_notation_unquoted));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty: \"\"\n"
			"ctrl: \"\\u001f\"\n"
			"string: \"Hello World!\"\n"
			"_host_: localhost\n"
			"config.cipher: aes256-ctr\n"
		);
	}

	SUBCASE("Raw String")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("empty", eclog::StringDesc("", eclog::string_notation_raw));
			root.renderMember("ctrl", eclog::StringDesc("\x1f", eclog::string_notation_raw));
			root.renderMember("string", eclog::StringDesc("Hello\nWorld!", eclog::string_notation_raw));
			root.renderMember("path", eclog::StringDesc("C:\\Program Files\\Internet Explorer", eclog::string_notation_raw));
			root.renderMember("string_2", eclog::StringDesc("\"Hello World!\"", eclog::string_notation_raw));
			root.renderMember("string_3",  eclog::StringDesc("\"Hello World!\"", eclog::string_notation_raw, "dd"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty: @\"\"\n"
			"ctrl: \"\\u001f\"\n"
			"string: \"Hello\\nWorld!\"\n"
			"path: @\"C:\\Program Files\\Internet Explorer\"\n"
			"string_2: \"\\\"Hello World!\\\"\"\n"
			"string_3: @dd\"\"Hello World!\"\"dd\n"
		);
	}

	SUBCASE("Heredoc")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("empty", eclog::StringDesc("", eclog::string_notation_heredoc, "HEREDOC"));
			root.renderMember("ctrl", eclog::StringDesc("\x1f", eclog::string_notation_heredoc, "HEREDOC"));
			root.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_heredoc, "HEREDOC"));
			root.renderMember(
				"Spoon Boy",
				eclog::StringDesc(
					"\tDo not try and bend the spoon, that's impossible.\n"
					"    Instead, only try to realize the truth... there is no\n"
					"spoon. Then you'll see that it is not the spoon that\n"
					"bends, it is only yourself.",
					eclog::string_notation_heredoc, "HEREDOC"));

			root.renderMember(
				eclog::KeyDesc("key", eclog::string_notation_heredoc, "HEREDOC"),
				eclog::StringDesc("string", eclog::string_notation_heredoc, "HEREDOC"));

			root.renderMember(
				eclog::KeyDesc("HEREDOC", eclog::string_notation_heredoc, "HEREDOC"),
				eclog::StringDesc("HEREDOC", eclog::string_notation_heredoc, "HEREDOC"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty: |HEREDOC\n"
			"\tHEREDOC\n"
			"ctrl: \"\\u001f\"\n"
			"string: |HEREDOC\n"
			"\tHello World!\n"
			"\tHEREDOC\n"
			"\"Spoon Boy\": |HEREDOC\n"
			"\t\tDo not try and bend the spoon, that's impossible.\n"
			"\t    Instead, only try to realize the truth... there is no\n"
			"\tspoon. Then you'll see that it is not the spoon that\n"
			"\tbends, it is only yourself.\n"
			"\tHEREDOC\n"
			"|HEREDOC\n"
			"\tkey\n"
			"\tHEREDOC\n"
			": |HEREDOC\n"
			"\tstring\n"
			"\tHEREDOC\n"
			"\"HEREDOC\": \"HEREDOC\"\n"
		);
	}

	SUBCASE("Number")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", 0);
			root.renderMember("b", 0.0);
			root.renderMember("c", -0.0);
			root.renderMember("d", 123456789);
			root.renderMember("e", 1.0 / 7.0);
			root.renderMember("f", std::numeric_limits<long long>::max());
			root.renderMember("g", std::numeric_limits<double>::max());
			root.renderMember("h", eclog::NumberDesc(1.0 / 7.0, 15));
			root.renderMember("i", eclog::NumberDesc(1.0 / 7.0, 4));
			root.renderMember("j", eclog::NumberDesc(1.0 / 7.0, 2));
			root.renderMember("k", eclog::NumberDesc(1.0 / 7.0, 1));
			root.renderMember("l", eclog::NumberDesc(1.0 / 7.0, 0));

			root.renderMember("m", eclog::Number::nan());
			root.renderMember("n", eclog::Number::negNan());
			root.renderMember("o", eclog::Number::infinity());
			root.renderMember("p", eclog::Number::negInfinity());
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"a: 0\n"
			"b: 0\n"
			"c: -0\n"
			"d: 123456789\n"
			"e: 0.14285714285714285\n"
			"f: 9223372036854775807\n"
			"g: 1.7976931348623157e308\n"
			"h: 0.142857142857143\n"
			"i: 0.1429\n"
			"j: 0.14\n"
			"k: 0.1\n"
			"l: 0\n"
			"m: nan\n"
			"n: -nan\n"
			"o: inf\n"
			"p: -inf\n"
		);
	}

	SUBCASE("Object")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.beginObject("empty");
			root.endObject();

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();

			root.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
			root.renderMember("str", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty:\n"
			"{\n"
			"}\n"
			"object:\n"
			"{\n"
			"\ta: null\n"
			"\tb: true\n"
			"\tstring: @dd\"Hello World!\"dd\n"
			"\thost: localhost\n"
			"\tn: 0.1428571\n"
			"\tm: 0.14285714285714285\n"
			"}\n"
			"n: 0.1428571\n"
			"str: @dd\"Hello World!\"dd\n"
		);
	}

	SUBCASE("Array")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.beginArray("empty");
			root.endArray();

			root.beginArray("array");
			{
				eclog::ArrayRenderer arr(root);

				arr.renderMember(eclog::null);
				arr.renderMember(true);
				arr.renderMember(eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				arr.renderMember(eclog::StringDesc("localhost", eclog::string_notation_unquoted));

				arr.beginArray();
				{
					eclog::ArrayRenderer arr2(arr);

					arr2.renderMember(11);
					arr2.renderMember(22);
					arr2.renderMember(33);
				}
				arr.endArray();

				arr.renderMember(eclog::NumberDesc(1.0 / 7.0, 7));
				arr.renderMember(eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endArray();

			root.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
			root.renderMember("str", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty:\n"
			"[\n"
			"]\n"
			"array:\n"
			"[\n"
			"\tnull\n"
			"\ttrue\n"
			"\t@dd\"Hello World!\"dd\n"
			"\tlocalhost\n"
			"\t[\n"
			"\t\t11\n"
			"\t\t22\n"
			"\t\t33\n"
			"\t]\n"
			"\t0.1428571\n"
			"\t0.14285714285714285\n"
			"]\n"
			"n: 0.1428571\n"
			"str: @dd\"Hello World!\"dd\n"
		);
	}

	SUBCASE("Render Root Object")
	{
		typedef eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> KeyValuePairDesc;
		typedef eclog::ValueDesc ValueDesc;

		ValueDesc vd2[] =
		{
			ValueDesc(1.0),
			ValueDesc(2.0),
			ValueDesc(3.0),
		};

		KeyValuePairDesc pd3[] =
		{
			KeyValuePairDesc("a", eclog::null),
			KeyValuePairDesc("b", true),
			KeyValuePairDesc("c", 1.0),
			KeyValuePairDesc("d", eclog::StringDesc("Hello World", eclog::string_notation_unquoted)),
		};

		ValueDesc vd[] =
		{
			ValueDesc(eclog::null),
			ValueDesc(true),
			ValueDesc(vd2),
			ValueDesc("Hello World"),
			ValueDesc(pd3),
		};

		KeyValuePairDesc pd2[] =
		{
			KeyValuePairDesc("a", eclog::null),
			KeyValuePairDesc("b", true),
			KeyValuePairDesc("c", 1.0),
			KeyValuePairDesc("d", eclog::StringDesc("Hello World", eclog::string_notation_raw, "dd")),
			KeyValuePairDesc("e", vd),
		};

		KeyValuePairDesc pd[] =
		{
			KeyValuePairDesc("1", eclog::null),
			KeyValuePairDesc("2", true),
			KeyValuePairDesc("3", 1.0),
			KeyValuePairDesc("4", "Hello World"),
			KeyValuePairDesc("5", pd2),
		};

		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.renderRootObject(pd);

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "\"1\": null\n\"2\": true\n\"3\": 1\n\"4\": \"Hello World\"\n\"5\":\n{\n"
			"\ta: null\n\tb: true\n\tc: 1\n\td: @dd\"Hello World\"dd\n\te:\n\t[\n\t\tnull\n\t\ttrue\n"
			"\t\t[\n\t\t\t1\n\t\t\t2\n\t\t\t3\n\t\t]\n\t\t\"Hello World\"\n\t\t{\n\t\t\ta: null\n\t\t"
			"\tb: true\n\t\t\tc: 1\n\t\t\td: \"Hello World\"\n\t\t}\n\t]\n}\n");
	}

	SUBCASE("Normal")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.linebreak = eclog::CRLF;
		rc.indentCharacter = eclog::RendererConfig::indent_character_space;
		rc.indentSize = 4;
        rc.placeOpenBracketOnNewLineForArrays = false;

		eclog::Renderer renderer(stream, rc);

		renderer.renderComment("Test Case");

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", true);
			root.renderMember("b", false);

			root.renderEmptyLines(1);

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderEmptyLines(1);

				obj.beginObject("object");
				{
					eclog::ObjectRenderer obj2(obj);

					obj2.renderMember("a", eclog::null);
					obj2.renderMember("b", true);
					obj2.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_unquoted, "dd"));
					obj2.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
					obj2.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
					obj2.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
				}
				obj.endObject();

				obj.renderEmptyLines(2);

				obj.beginArray("array");
				{
					eclog::ArrayRenderer arr(obj);

					arr.renderComment("Array");

					for (int j = 0; j < 10; ++j)
					{
						arr.beginInline();

						for (int i = 0; i < 5; ++i)
						{
							arr.renderMember(2 * i + j);
						}

						arr.endInline();
					}

					arr.renderEmptyLines(1);

					arr.beginObject();
					{
						eclog::ObjectRenderer obj3(arr);

						obj3.renderMember(
							"Spoon Boy",
							eclog::StringDesc(
								"Do not try and bend the spoon, that's impossible.\n"
								"Instead, only try to realize the truth... there is no\n"
								"spoon. Then you'll see that it is not the spoon that\n"
								"bends, it is only yourself.",
								eclog::string_notation_heredoc, "HEREDOC"));
					}
					arr.endObject();
				}
				obj.endArray();

				obj.renderEmptyLines(1);

				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"# Test Case\r\n"
			"a: true\r\n"
			"b: false\r\n"
			"\r\n"
			"object:\r\n"
			"{\r\n"
			"    a: null\r\n"
			"    b: true\r\n"
			"    string: @dd\"Hello World!\"dd\r\n"
			"    host: localhost\r\n"
			"    n: 0.1428571\r\n"
			"\r\n"
			"    object:\r\n"
			"    {\r\n"
			"        a: null\r\n"
			"        b: true\r\n"
			"        string: \"Hello World!\"\r\n"
			"        host: localhost\r\n"
			"        n: 0.1428571\r\n"
			"        m: 0.14285714285714285\r\n"
			"    }\r\n"
			"\r\n"
			"\r\n"
			"    array: [\r\n"
			"        # Array\r\n"
			"        0, 2, 4, 6, 8\r\n"
			"        1, 3, 5, 7, 9\r\n"
			"        2, 4, 6, 8, 10\r\n"
			"        3, 5, 7, 9, 11\r\n"
			"        4, 6, 8, 10, 12\r\n"
			"        5, 7, 9, 11, 13\r\n"
			"        6, 8, 10, 12, 14\r\n"
			"        7, 9, 11, 13, 15\r\n"
			"        8, 10, 12, 14, 16\r\n"
			"        9, 11, 13, 15, 17\r\n"
			"\r\n"
			"        {\r\n"
			"            \"Spoon Boy\": |HEREDOC\r\n"
			"                Do not try and bend the spoon, that's impossible.\r\n"
			"                Instead, only try to realize the truth... there is no\r\n"
			"                spoon. Then you'll see that it is not the spoon that\r\n"
			"                bends, it is only yourself.\r\n"
			"                HEREDOC\r\n"
			"        }\r\n"
			"    ]\r\n"
			"\r\n"
			"    m: 0.14285714285714285\r\n"
			"}\r\n"
		);
	}

	SUBCASE("Compact")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

        rc.formatting = eclog::RendererConfig::formatting_compact;
		rc.linebreak = eclog::CRLF;
		rc.indentCharacter = eclog::RendererConfig::indent_character_space;
		rc.indentSize = 4;
        rc.placeOpenBracketOnNewLineForArrays = false;

		eclog::Renderer renderer(stream, rc);

		renderer.renderComment("Test Case");

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", true);
			root.renderMember("b", false);

			root.renderEmptyLines(1);

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderEmptyLines(1);

				obj.beginObject("object");
				{
					eclog::ObjectRenderer obj2(obj);

					obj2.renderMember("a", eclog::null);
					obj2.renderMember("b", true);
					obj2.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_unquoted, "dd"));
					obj2.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
					obj2.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
					obj2.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
				}
				obj.endObject();

				obj.renderEmptyLines(2);

				obj.beginArray("array");
				{
					eclog::ArrayRenderer arr(obj);

					arr.renderComment("Array");

					for (int j = 0; j < 10; ++j)
					{
						arr.beginInline();

						for (int i = 0; i < 5; ++i)
						{
							arr.renderMember(2 * i + j);
						}

						arr.endInline();
					}

					arr.renderEmptyLines(1);

					arr.beginObject();
					{
						eclog::ObjectRenderer obj3(arr);

						obj3.renderMember(
							"Spoon Boy",
							eclog::StringDesc(
								"Do not try and bend the spoon, that's impossible.\n"
								"Instead, only try to realize the truth... there is no\n"
								"spoon. Then you'll see that it is not the spoon that\n"
								"bends, it is only yourself.",
								eclog::string_notation_heredoc, "HEREDOC"));
					}
					arr.endObject();
				}
				obj.endArray();

				obj.renderEmptyLines(1);

				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"a:true,b:false,object:{a:null,b:true,string:@dd\"Hello World!\"dd,host:localhost,n:0.1428571,object:{a:null,b:true,"
			"string:\"Hello World!\",host:localhost,n:0.1428571,m:0.14285714285714285},array:[0,2,4,6,8,1,3,5,7,9,2,4,6,8,10,3,5,"
			"7,9,11,4,6,8,10,12,5,7,9,11,13,6,8,10,12,14,7,9,11,13,15,8,10,12,14,16,9,11,13,15,17,{\"Spoon Boy\":\"Do not try and bend"
			" the spoon, that's impossible.\\nInstead, only try to realize the truth... there is no\\nspoon. Then you'll see that it is"
			" not the spoon that\\nbends, it is only yourself.\"}],m:0.14285714285714285}"
		);
	}

	SUBCASE("Config Basics #1")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.encloseRootObjectWithCurlyBrackets = true;

		eclog::Renderer renderer(stream, rc);

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "{\n}\n");
	}

	SUBCASE("Config Basics #2")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.formatting = eclog::RendererConfig::formatting_compact;
		rc.encloseRootObjectWithCurlyBrackets = true;

		eclog::Renderer renderer(stream, rc);

		renderer.close();

		std::string text = oss.str();

		CHECK(text == "{}");
	}

	SUBCASE("Config Basics #3")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.useQuotedStringsOnly = true;

		eclog::Renderer renderer(stream, rc);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("empty", eclog::StringDesc("", eclog::string_notation_unquoted));
			root.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_unquoted));
			root.renderMember("_host_", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
			root.renderMember("config.cipher", eclog::StringDesc("aes256-ctr", eclog::string_notation_unquoted));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"\"empty\": \"\"\n"
			"\"string\": \"Hello World!\"\n"
			"\"_host_\": \"localhost\"\n"
			"\"config.cipher\": \"aes256-ctr\"\n"
		);
	}

	SUBCASE("Config Basics #4")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.useCommasToSeparateItems = true;

		eclog::Renderer renderer(stream, rc);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.beginObject("empty");
			root.endObject();

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();

			root.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
			root.renderMember("str", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"empty:\n"
			"{\n"
			"},\n"
			"object:\n"
			"{\n"
			"\ta: null,\n"
			"\tb: true,\n"
			"\tstring: @dd\"Hello World!\"dd,\n"
			"\thost: localhost,\n"
			"\tn: 0.1428571,\n"
			"\tm: 0.14285714285714285\n"
			"},\n"
			"n: 0.1428571,\n"
			"str: @dd\"Hello World!\"dd\n"
		);
	}

	SUBCASE("Config Basics #5")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.encloseRootObjectWithCurlyBrackets = true;
		rc.useCommasToSeparateItems = true;

		eclog::Renderer renderer(stream, rc);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.beginObject("empty");
			root.endObject();

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();

			root.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
			root.renderMember("str", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"{\n"
			"\tempty:\n"
			"\t{\n"
			"\t},\n"
			"\tobject:\n"
			"\t{\n"
			"\t\ta: null,\n"
			"\t\tb: true,\n"
			"\t\tstring: @dd\"Hello World!\"dd,\n"
			"\t\thost: localhost,\n"
			"\t\tn: 0.1428571,\n"
			"\t\tm: 0.14285714285714285\n"
			"\t},\n"
			"\tn: 0.1428571,\n"
			"\tstr: @dd\"Hello World!\"dd\n"
			"}\n"
		);
	}

	SUBCASE("Config Basics #6")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc;

		rc.useStringsToRepresentInfinitiesAndNaNs = true;

		eclog::Renderer renderer(stream, rc);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", 0);
			root.renderMember("b", 0.0);
			root.renderMember("c", -0.0);
			root.renderMember("d", 123456789);
			root.renderMember("e", 1.0 / 7.0);
			root.renderMember("f", std::numeric_limits<long long>::max());
			root.renderMember("g", std::numeric_limits<double>::max());
			root.renderMember("h", eclog::NumberDesc(1.0 / 7.0, 15));
			root.renderMember("i", eclog::NumberDesc(1.0 / 7.0, 4));
			root.renderMember("j", eclog::NumberDesc(1.0 / 7.0, 2));
			root.renderMember("k", eclog::NumberDesc(1.0 / 7.0, 1));
			root.renderMember("l", eclog::NumberDesc(1.0 / 7.0, 0));

			root.renderMember("m", eclog::Number::nan());
			root.renderMember("n", eclog::Number::negNan());
			root.renderMember("o", eclog::Number::infinity());
			root.renderMember("p", eclog::Number::negInfinity());
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"a: 0\n"
			"b: 0\n"
			"c: -0\n"
			"d: 123456789\n"
			"e: 0.14285714285714285\n"
			"f: 9223372036854775807\n"
			"g: 1.7976931348623157e308\n"
			"h: 0.142857142857143\n"
			"i: 0.1429\n"
			"j: 0.14\n"
			"k: 0.1\n"
			"l: 0\n"
			"m: \"nan\"\n"
			"n: \"-nan\"\n"
			"o: \"inf\"\n"
			"p: \"-inf\"\n"
		);
	}

	SUBCASE("Config Basics #7")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::Renderer renderer(stream);

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("escape", eclog::cstring("\\/\"\0\b\f\n\r\t", 9));
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"escape: \"\\\\/\\\"\\u0000\\b\\f\\n\\r\\t\"\n"
		);
	}

	SUBCASE("Config JSON Compatible")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc(eclog::RendererConfig::scheme_json_compatible);

		rc.linebreak = eclog::CRLF;
		rc.indentCharacter = eclog::RendererConfig::indent_character_space;
		rc.indentSize = 4;
		rc.placeOpenBracketOnNewLineForArrays = false;

		eclog::Renderer renderer(stream, rc);

		renderer.renderComment("JSON");

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", true);
			root.renderMember("b", false);

			root.renderEmptyLines(1);

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderEmptyLines(1);

				obj.beginObject("object");
				{
					eclog::ObjectRenderer obj2(obj);

					obj2.renderMember("a", eclog::null);
					obj2.renderMember("b", true);
					obj2.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_unquoted, "dd"));
					obj2.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
					obj2.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
					obj2.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
				}
				obj.endObject();

				obj.renderEmptyLines(2);

				obj.beginArray("array");
				{
					eclog::ArrayRenderer arr(obj);

					arr.renderComment("Array");

					arr.renderMember(eclog::Number::nan());
					arr.renderMember(eclog::Number::negNan());
					arr.renderMember(eclog::Number::infinity());
					arr.renderMember(eclog::Number::negInfinity());

					for (int j = 0; j < 10; ++j)
					{
						arr.beginInline();

						for (int i = 0; i < 5; ++i)
						{
							arr.renderMember(2 * i + j);
						}

						arr.endInline();
					}

					arr.renderEmptyLines(1);

					arr.beginObject();
					{
						eclog::ObjectRenderer obj3(arr);

						obj3.renderMember(
							"Spoon Boy",
							eclog::StringDesc(
								"Do not try and bend the spoon, that's impossible.\n"
								"Instead, only try to realize the truth... there is no\n"
								"spoon. Then you'll see that it is not the spoon that\n"
								"bends, it is only yourself.",
								eclog::string_notation_heredoc, "HEREDOC"));
					}
					arr.endObject();
				}
				obj.endArray();

				obj.renderEmptyLines(1);

				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"{\r\n"
			"    \"a\": true,\r\n"
			"    \"b\": false,\r\n"
			"\r\n"
			"    \"object\":\r\n"
			"    {\r\n"
			"        \"a\": null,\r\n"
			"        \"b\": true,\r\n"
			"        \"string\": \"Hello World!\",\r\n"
			"        \"host\": \"localhost\",\r\n"
			"        \"n\": 0.1428571,\r\n"
			"\r\n"
			"        \"object\":\r\n"
			"        {\r\n"
			"            \"a\": null,\r\n"
			"            \"b\": true,\r\n"
			"            \"string\": \"Hello World!\",\r\n"
			"            \"host\": \"localhost\",\r\n"
			"            \"n\": 0.1428571,\r\n"
			"            \"m\": 0.14285714285714285\r\n"
			"        },\r\n"
			"\r\n"
			"\r\n"
			"        \"array\": [\r\n"
			"            \"nan\",\r\n"
			"            \"-nan\",\r\n"
			"            \"inf\",\r\n"
			"            \"-inf\",\r\n"
			"            0, 2, 4, 6, 8,\r\n"
			"            1, 3, 5, 7, 9,\r\n"
			"            2, 4, 6, 8, 10,\r\n"
			"            3, 5, 7, 9, 11,\r\n"
			"            4, 6, 8, 10, 12,\r\n"
			"            5, 7, 9, 11, 13,\r\n"
			"            6, 8, 10, 12, 14,\r\n"
			"            7, 9, 11, 13, 15,\r\n"
			"            8, 10, 12, 14, 16,\r\n"
			"            9, 11, 13, 15, 17,\r\n"
			"\r\n"
			"            {\r\n"
			"                \"Spoon Boy\": \"Do not try and bend the spoon, that's impossible.\\n"
			"Instead, only try to realize the truth... there is no\\nspoon. Then you'll see that it"
			" is not the spoon that\\nbends, it is only yourself.\"\r\n"
			"            }\r\n"
			"        ],\r\n"
			"\r\n"
			"        \"m\": 0.14285714285714285\r\n"
			"    }\r\n"
			"}\r\n"
		);
	}

	SUBCASE("Config JSON Compatible #2")
	{
		std::ostringstream oss;

		eclog::StdStreamOutputStream stream(oss);

		eclog::RendererConfig rc(eclog::RendererConfig::scheme_json_compatible);

		rc.formatting = eclog::RendererConfig::formatting_compact;

		eclog::Renderer renderer(stream, rc);

		renderer.renderComment("JSON");

		renderer.beginRootObject();
		{
			eclog::ObjectRenderer root(renderer);

			root.renderMember("a", true);
			root.renderMember("b", false);

			root.renderEmptyLines(1);

			root.beginObject("object");
			{
				eclog::ObjectRenderer obj(root);

				obj.renderMember("a", eclog::null);
				obj.renderMember("b", true);
				obj.renderMember("string", eclog::StringDesc("Hello World!", eclog::string_notation_raw, "dd"));
				obj.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
				obj.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
				obj.renderEmptyLines(1);

				obj.beginObject("object");
				{
					eclog::ObjectRenderer obj2(obj);

					obj2.renderMember("a", eclog::null);
					obj2.renderMember("b", true);
					obj2.renderMember("string", eclog::cstring("Hello\0World!", 12));
					obj2.renderMember("host", eclog::StringDesc("localhost", eclog::string_notation_unquoted));
					obj2.renderMember("n", eclog::NumberDesc(1.0 / 7.0, 7));
					obj2.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
				}
				obj.endObject();

				obj.renderEmptyLines(2);

				obj.beginArray("array");
				{
					eclog::ArrayRenderer arr(obj);

					arr.renderMember(eclog::Number::nan());
					arr.renderMember(eclog::Number::negNan());
					arr.renderMember(eclog::Number::infinity());
					arr.renderMember(eclog::Number::negInfinity());

					for (int j = 0; j < 10; ++j)
					{
						arr.beginInline();

						for (int i = 0; i < 5; ++i)
						{
							arr.renderMember(2 * i + j);
						}

						arr.endInline();
					}

					arr.renderEmptyLines(1);

					arr.beginObject();
					{
						eclog::ObjectRenderer obj3(arr);

						obj3.renderMember(
							"Spoon Boy",
							eclog::StringDesc(
								"Do not try and bend the spoon, that's impossible.\n"
								"Instead, only try to realize the truth... there is no\n"
								"spoon. Then you'll see that it is not the spoon that\n"
								"bends, it is only yourself.",
								eclog::string_notation_heredoc, "HEREDOC"));
					}
					arr.endObject();
				}
				obj.endArray();

				obj.renderEmptyLines(1);

				obj.renderMember("m", eclog::NumberDesc(1.0 / 7.0, 17));
			}
			root.endObject();
		}
		renderer.endRootObject();

		renderer.close();

		std::string text = oss.str();

		CHECK(text ==
			"{\"a\":true,\"b\":false,\"object\":{\"a\":null,\"b\":true,\"string\":\"Hello World!\",\"host\":\"localhost\","
			"\"n\":0.1428571,\"object\":{\"a\":null,\"b\":true,\"string\":\"Hello\\u0000World!\",\"host\":\"localhost\",\"n\":0.1428571,"
			"\"m\":0.14285714285714285},\"array\":[\"nan\",\"-nan\",\"inf\",\"-inf\",0,2,4,6,8,1,3,5,7,9,2,4,6,8,10,3,5,7,9,11,4,6,8,10,12,5,7,9,11,13,6,8,10,12,14,7,"
			"9,11,13,15,8,10,12,14,16,9,11,13,15,17,{\"Spoon Boy\":\"Do not try and bend the spoon, that's impossible.\\nInstead, only"
			" try to realize the truth... there is no\\nspoon. Then you'll see that it is not the spoon that\\nbends,"
			" it is only yourself.\"}],\"m\":0.14285714285714285}}"
		);
	}
}

