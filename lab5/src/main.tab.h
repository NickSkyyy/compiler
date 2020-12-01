/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_MAIN_TAB_H_INCLUDED
# define YY_YY_SRC_MAIN_TAB_H_INCLUDED
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
    T_AND = 258,
    T_ASS = 259,
    T_DIV = 260,
    T_DIVE = 261,
    T_EQ = 262,
    T_LA = 263,
    T_LAE = 264,
    T_LE = 265,
    T_LEE = 266,
    T_MINE = 267,
    T_MINS = 268,
    T_MOD = 269,
    T_MODE = 270,
    T_MUL = 271,
    T_MULE = 272,
    T_NOT = 273,
    T_NOTE = 274,
    T_OR = 275,
    T_PLUE = 276,
    T_PLUS = 277,
    ID = 278,
    BOOL = 279,
    CHAR = 280,
    INT = 281,
    STRING = 282,
    BREAK = 283,
    CONST = 284,
    CONTINUE = 285,
    ELSE = 286,
    FOR = 287,
    IF = 288,
    MAIN = 289,
    RETURN = 290,
    TYPE = 291,
    WHILE = 292,
    COMA = 293,
    LBRAC = 294,
    RBRAC = 295,
    LPATH = 296,
    RPATH = 297,
    SEMI = 298,
    CHAR_IN = 299,
    INT_IN = 300,
    STR_IN = 301,
    CHAR_OUT = 302,
    INT_OUT = 303,
    STR_OUT = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MAIN_TAB_H_INCLUDED  */
