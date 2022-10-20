/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0

#include <tools/yulPrettyPrinter/YulPrettyPrinter.h>
#include <tools/yulPrettyPrinter/Exceptions.h>

#include <libyul/Utilities.h>

#include <libsolutil/Assertions.h>
#include <libsolutil/CommonIO.h>

#include <iostream>

using namespace std;

using namespace solidity::util;
using namespace solidity::yul;
namespace po = boost::program_options;

namespace solidity::yulprettyprinter
{

void YulPrettyPrinter::main(int _argc, char** _argv)
{
	optional<po::variables_map> arguments = parseCommandLine(_argc, _argv);
	if (!arguments.has_value())
		return;
}

YulPrettyPrinter::CommandLineDescription YulPrettyPrinter::buildCommandLineDescription()
{
	unsigned const lineLength = po::options_description::m_default_line_length;
	unsigned const minDescriptionLength = lineLength - 23;

	po::options_description keywordDescription(
		"yul-prettyprinter, a tool for formatting Yul code.\n"
		"\n"
		"Usage: yul-prettyprinter <file>\n"
		"Reads <file> as Yul code and prints out the formatted version if the code is valid.\n"
		"Example:\n"
		"yul-prettyprinter program.yul",
		lineLength,
		minDescriptionLength
	);

	po::positional_options_description positionalDescription;
	positionalDescription.add("input-files", -1);

	return {keywordDescription, positionalDescription};
}

optional<po::variables_map> YulPrettyPrinter::parseCommandLine(int _argc, char** _argv)
{
	auto [keywordDescription, positionalDescription] = buildCommandLineDescription();

	po::variables_map arguments;
	po::notify(arguments);

	po::command_line_parser parser(_argc, _argv);
	parser.options(keywordDescription).positional(positionalDescription);
	po::store(parser.run(), arguments);

	if (arguments.count("help") > 0)
	{
		cout << keywordDescription << endl;
		return nullopt;
	}

	if (arguments.count("input-files") == 0)
		assertThrow(false, NoInputFiles, "Missing argument: input-files.");

	return arguments;
}

static void prettyPrintYul(
	boost::program_options::variables_map const& _arguments
)
{
	auto& sourceFileOptions = _arguments["input-files"].as<vector<string>>();

	for (auto& path: sourceFileOptions) {
		assertThrow(boost::filesystem::exists(path), MissingFile, "Source file does not exist: " + path);
		string sourceCode = readFileAsString(path);
		cout << reindent(sourceCode) << endl;
	}
}

}
