# BNFBusters Decafast

Implementation of Lexical Parser built on the Lexical Analyzer component for a compiler for the Decaf programming languaged defined on
http://anoopsarkar.github.io/compilers-class/decafspec.html
Using Flex and Bison/YACC

## Installation

Use the command

	$make

To generate the executable decafast

## Usage

Run the executable and manually enter Decaf programs
OR 
Pipe Decaf files into the lexer application

## History

18 Jun, 2016
200/200																							mingkaic authored
132/132																							mingkaic authored
131/132. fixed all except arith1: issue short circuit evaluation  								mingkaic authored
113/124  																						mingkaic authored
49/124  																						mingkaic authored
implemented all except expr and ops  															mingkaic authored
implemented branching for extern and field declaration of package  								mingkaic authored
added decaf statements to decafast.y  															mingkaic authored
fixed size pointers, readded zip scripts  														mingkaic authored

17 Jun, 2016
implemented branching for extern and field declaration of package								mingkaic authored
added decaf statements to decafast.y															mingkaic authored
fixed size pointers, readded zip scripts														mingkaic authored

16 Jun, 2016
restructure + lexer integrated into parser														mingkaic authored

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
- defined some obvious error cases for the lexer analyzer
- implemented decaf parser

Nav Kalra

- defined most of the error cases for the lexer analyzer