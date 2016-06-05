# BNFBusters Decaflex

Implementation of Lexical Analyzer component for a compiler for the Decaf programming languaged defined on
http://anoopsarkar.github.io/compilers-class/decafspec.html
Using Flex

## Installation

Use the command

	make decaflex

To generate the executable decaflex

## Usage

Run the executable and manually enter Decaf programs
OR 
Pipe Decaf files into the lexer application

## History

04 Jun, 2016
Added error case for character literals 														nkalra authored

28 May, 2016
59/59 + changed lexeme.pop_back to lexeme.erase to support compilers not supporting c++11  		mingkaic authored
57/59  																							mingkaic authored   
removed .DS_Store, included decaflex.lex  														mingkaic authored 
40/59 																							mingkaic authored

27 May, 2016
initial commit 																					mingkaic authored 

## Credits

Ming Kai Chen

- constructed well-defined token definitions (both keywords and literals)
- edited outputs to match test format
- defined some obvious error cases

Nav Kalra

- defined most of the error cases