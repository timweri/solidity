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
/**
 * Contains the main class that handles command-line parameters and
 * logic to format yul
 */
#pragma once

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <tools/yulPhaser/Exceptions.h>

#include <istream>
#include <ostream>
#include <string>

namespace solidity::yulprettyprinter
{

/**
 * Main class that parses command-line parameters and the logic to format
 * yul using existing libraries.
 */
class YulPrettyPrinter
{
public:
	static void main(int argc, char** argv);

private:
	struct CommandLineDescription
	{
		boost::program_options::options_description keywordDescription;
		boost::program_options::positional_options_description positionalDescription;
	};

	static CommandLineDescription buildCommandLineDescription();
	static std::optional<boost::program_options::variables_map> parseCommandLine(int _argc, char** _argv);
	static void prettyPrintYul(
		boost::program_options::variables_map const& _arguments
	);
};

}
