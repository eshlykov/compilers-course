/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_MINIJAVA_PARSER_TAB_H_INCLUDED
# define YY_YY_MINIJAVA_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TT_Number = 258,
    TT_Identifier = 259,
    TT_Eof = 260,
    TT_Class = 261,
    TT_Public = 262,
    TT_Static = 263,
    TT_Void = 264,
    TT_Main = 265,
    TT_LeftBracket = 266,
    TT_RightBracket = 267,
    TT_LeftParen = 268,
    TT_RightParen = 269,
    TT_LeftBrace = 270,
    TT_RightBrace = 271,
    TT_Return = 272,
    TT_If = 273,
    TT_Print = 274,
    TT_String = 275,
    TT_New = 276,
    TT_Dot = 277,
    TT_Semicolon = 278,
    TT_Extends = 279,
    TT_Length = 280,
    TT_Else = 281,
    TT_While = 282,
    TT_Boolean = 283,
    TT_True = 284,
    TT_False = 285,
    TT_This = 286,
    TT_Int = 287,
    TT_Bang = 288,
    TT_And = 289,
    TT_Less = 290,
    TT_Plus = 291,
    TT_Minus = 292,
    TT_Star = 293,
    TT_Assignment = 294,
    TT_Comma = 295,
    TT_Error = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "minijava-parser.y" /* yacc.c:1919  */

    int Number;
    char* Identifier;

#line 101 "minijava-parser.tab.h" /* yacc.c:1919  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MINIJAVA_PARSER_TAB_H_INCLUDED  */
