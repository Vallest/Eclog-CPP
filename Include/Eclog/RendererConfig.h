// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_RENDERERCONFIG_H_
#define ECLOG_CPP_RENDERERCONFIG_H_

#include <Eclog/Linebreak.h>

namespace eclog {

	struct RendererConfig {
	public:
		enum Scheme {
			scheme_typical,
			scheme_json_compatible,
		};

		enum Formatting {
			formatting_regular,
			formatting_compact,
		};

		enum IndentCharacter {
			indent_character_tab,
			indent_character_space,
		};

	public:
		explicit RendererConfig(Scheme scheme = scheme_typical)
		{
			formatting = formatting_regular;
			linebreak = LF;
			indentCharacter = indent_character_tab;
			indentSize = 1;
            insertSpaceAfterColon = true;
            placeOpenBracketOnNewLineForObjects = true;
            placeOpenBracketOnNewLineForArrays = true;

			if (scheme == scheme_typical)
			{
				encloseRootObjectWithCurlyBrackets = false;
				useQuotedStringsOnly = false;
				useCommasToSeparateItems = false;
				useStringsToRepresentInfinitiesAndNaNs = false;
				enableComments = true;
			}
			else if (scheme == scheme_json_compatible)
			{
				encloseRootObjectWithCurlyBrackets = true;
				useQuotedStringsOnly = true;
				useCommasToSeparateItems = true;
				useStringsToRepresentInfinitiesAndNaNs = true;
				enableComments = false;
			}
		}

	public:
		Formatting formatting;

		Linebreak linebreak;

		IndentCharacter indentCharacter;
		int indentSize;

        bool insertSpaceAfterColon;

        bool placeOpenBracketOnNewLineForObjects;

        bool placeOpenBracketOnNewLineForArrays;

		bool encloseRootObjectWithCurlyBrackets;

		bool useQuotedStringsOnly;

		bool useCommasToSeparateItems;

		bool useStringsToRepresentInfinitiesAndNaNs;

		bool enableComments;
	};

} // eclog

#endif // ECLOG_CPP_RENDERERCONFIG_H_

