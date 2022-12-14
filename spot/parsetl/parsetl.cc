// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   tlyylex



#include "parsetl.hh"


// Unqualified %code blocks.
#line 59 "parsetl.yy"

/* parsetl.hh and parsedecl.hh include each other recursively.
   We mut ensure that YYSTYPE is declared (by the above %union)
   before parsedecl.hh uses it. */
#include <spot/parsetl/parsedecl.hh>
using namespace spot;

#define missing_right_op_msg(op, str)		\
  error_list.emplace_back(op,			\
    "missing right operand for \"" str "\"");

#define missing_right_op(res, op, str)		\
  do						\
    {						\
      missing_right_op_msg(op, str);		\
      res = fnode::ff();		\
    }						\
  while (0);

// right is missing, so complain and use left.
#define missing_right_binop(res, left, op, str)	\
  do						\
    {						\
      missing_right_op_msg(op, str);		\
      res = left;				\
    }						\
  while (0);

// right is missing, so complain and use false.
#define missing_right_binop_hard(res, left, op, str)	\
  do							\
    {							\
      left->destroy();					\
      missing_right_op(res, op, str);			\
    }							\
  while (0);

  static bool
  sere_ensure_bool(const fnode* f, const spot::location& loc,
                   const char* oper, spot::parse_error_list& error_list)
  {
    if (f->is_boolean())
      return true;
    std::string s;
    s.reserve(80);
    s = "not a Boolean expression: in a SERE ";
    s += oper;
    s += " can only be applied to a Boolean expression";
    error_list.emplace_back(loc, s);
    return false;
  }

  static const fnode*
  error_false_block(const spot::location& loc,
                    spot::parse_error_list& error_list)
  {
    error_list.emplace_back(loc, "treating this block as false");
    return fnode::ff();
  }

  static const fnode*
  parse_ap(const std::string& str,
           const spot::location& location,
           spot::environment& env,
           spot::parse_error_list& error_list)
  {
    auto res = env.require(str);
    if (!res)
      {
        std::string s;
        s.reserve(64);
        s = "unknown atomic proposition `";
        s += str;
        s += "' in ";
        s += env.name();
        error_list.emplace_back(location, s);
      }
    return res.to_node_();
  }

  enum parser_type { parser_ltl, parser_bool, parser_sere };

  static const fnode*
  try_recursive_parse(const std::string& str,
		      const spot::location& location,
		      spot::environment& env,
		      bool debug,
		      parser_type type,
		      spot::parse_error_list& error_list)
    {
      // We want to parse a U (b U c) as two until operators applied
      // to the atomic propositions a, b, and c.  We also want to
      // parse a U (b == c) as one until operator applied to the
      // atomic propositions "a" and "b == c".  The only problem is
      // that we do not know anything about "==" or in general about
      // the syntax of atomic proposition of our users.
      //
      // To support that, the lexer will return "b U c" and "b == c"
      // as PAR_BLOCK tokens.  We then try to parse such tokens
      // recursively.  If, as in the case of "b U c", the block is
      // successfully parsed as a formula, we return this formula.
      // Otherwise, we convert the string into an atomic proposition
      // (it's up to the environment to check the syntax of this
      // proposition, and maybe reject it).

      if (str.empty())
	{
	  error_list.emplace_back(location, "unexpected empty block");
	  return fnode::ff();
	}

      spot::parsed_formula pf;
      switch (type)
	{
	case parser_sere:
	  pf = spot::parse_infix_sere(str, env, debug, true);
	  break;
	case parser_bool:
	  pf = spot::parse_infix_boolean(str, env, debug, true);
	  break;
	case parser_ltl:
	  pf = spot::parse_infix_psl(str, env, debug, true);
	  break;
	}

      if (pf.errors.empty())
	return pf.f.to_node_();
      return parse_ap(str, location, env, error_list);
    }


#line 180 "parsetl.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if TLYYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !TLYYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !TLYYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace tlyy {
#line 272 "parsetl.cc"

  /// Build a parser object.
  parser::parser (spot::parse_error_list &error_list_yyarg, spot::environment &parse_environment_yyarg, spot::formula &result_yyarg)
#if TLYYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      error_list (error_list_yyarg),
      parse_environment (parse_environment_yyarg),
      result (result_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.kind ())
    {
      case symbol_kind::S_PAR_BLOCK: // "(...) block"
#line 284 "parsetl.yy"
                    { delete (yysym.value.str); }
#line 480 "parsetl.cc"
        break;

      case symbol_kind::S_BRA_BLOCK: // "{...} block"
#line 284 "parsetl.yy"
                    { delete (yysym.value.str); }
#line 486 "parsetl.cc"
        break;

      case symbol_kind::S_BRA_BANG_BLOCK: // "{...}! block"
#line 284 "parsetl.yy"
                    { delete (yysym.value.str); }
#line 492 "parsetl.cc"
        break;

      case symbol_kind::S_ATOMIC_PROP: // "atomic proposition"
#line 284 "parsetl.yy"
                    { delete (yysym.value.str); }
#line 498 "parsetl.cc"
        break;

      case symbol_kind::S_atomprop: // atomprop
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 504 "parsetl.cc"
        break;

      case symbol_kind::S_booleanatom: // booleanatom
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 510 "parsetl.cc"
        break;

      case symbol_kind::S_sere: // sere
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 516 "parsetl.cc"
        break;

      case symbol_kind::S_bracedsere: // bracedsere
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 522 "parsetl.cc"
        break;

      case symbol_kind::S_parenthesedsubformula: // parenthesedsubformula
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 528 "parsetl.cc"
        break;

      case symbol_kind::S_boolformula: // boolformula
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 534 "parsetl.cc"
        break;

      case symbol_kind::S_subformula: // subformula
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 540 "parsetl.cc"
        break;

      case symbol_kind::S_lbtformula: // lbtformula
#line 285 "parsetl.yy"
                    { (yysym.value.ltl)->destroy(); }
#line 546 "parsetl.cc"
        break;

      default:
        break;
    }
  }

#if TLYYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_PAR_BLOCK: // "(...) block"
#line 287 "parsetl.yy"
                 { debug_stream() << *(yysym.value.str); }
#line 574 "parsetl.cc"
        break;

      case symbol_kind::S_BRA_BLOCK: // "{...} block"
#line 287 "parsetl.yy"
                 { debug_stream() << *(yysym.value.str); }
#line 580 "parsetl.cc"
        break;

      case symbol_kind::S_BRA_BANG_BLOCK: // "{...}! block"
#line 287 "parsetl.yy"
                 { debug_stream() << *(yysym.value.str); }
#line 586 "parsetl.cc"
        break;

      case symbol_kind::S_OP_SQBKT_NUM: // "number for square bracket operator"
#line 290 "parsetl.yy"
                 { debug_stream() << (yysym.value.num); }
#line 592 "parsetl.cc"
        break;

      case symbol_kind::S_ATOMIC_PROP: // "atomic proposition"
#line 287 "parsetl.yy"
                 { debug_stream() << *(yysym.value.str); }
#line 598 "parsetl.cc"
        break;

      case symbol_kind::S_OP_DELAY_N: // "SVA delay operator"
#line 290 "parsetl.yy"
                 { debug_stream() << (yysym.value.num); }
#line 604 "parsetl.cc"
        break;

      case symbol_kind::S_sqbkt_num: // sqbkt_num
#line 290 "parsetl.yy"
                 { debug_stream() << (yysym.value.num); }
#line 610 "parsetl.cc"
        break;

      case symbol_kind::S_sqbracketargs: // sqbracketargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 616 "parsetl.cc"
        break;

      case symbol_kind::S_gotoargs: // gotoargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 622 "parsetl.cc"
        break;

      case symbol_kind::S_starargs: // starargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 628 "parsetl.cc"
        break;

      case symbol_kind::S_fstarargs: // fstarargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 634 "parsetl.cc"
        break;

      case symbol_kind::S_equalargs: // equalargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 640 "parsetl.cc"
        break;

      case symbol_kind::S_delayargs: // delayargs
#line 291 "parsetl.yy"
                 { debug_stream() << (yysym.value.minmax).min << ".." << (yysym.value.minmax).max; }
#line 646 "parsetl.cc"
        break;

      case symbol_kind::S_atomprop: // atomprop
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 652 "parsetl.cc"
        break;

      case symbol_kind::S_booleanatom: // booleanatom
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 658 "parsetl.cc"
        break;

      case symbol_kind::S_sere: // sere
#line 289 "parsetl.yy"
                 { print_sere(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 664 "parsetl.cc"
        break;

      case symbol_kind::S_bracedsere: // bracedsere
#line 289 "parsetl.yy"
                 { print_sere(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 670 "parsetl.cc"
        break;

      case symbol_kind::S_parenthesedsubformula: // parenthesedsubformula
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 676 "parsetl.cc"
        break;

      case symbol_kind::S_boolformula: // boolformula
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 682 "parsetl.cc"
        break;

      case symbol_kind::S_subformula: // subformula
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 688 "parsetl.cc"
        break;

      case symbol_kind::S_lbtformula: // lbtformula
#line 288 "parsetl.yy"
                 { print_psl(debug_stream(), formula((yysym.value.ltl)->clone())); }
#line 694 "parsetl.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if TLYYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // TLYYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, error_list));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // result: "LTL start marker" subformula "end of formula"
#line 295 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 950 "parsetl.cc"
    break;

  case 3: // result: "LTL start marker" enderror
#line 300 "parsetl.yy"
              {
		result = nullptr;
		YYABORT;
	      }
#line 959 "parsetl.cc"
    break;

  case 4: // result: "LTL start marker" subformula enderror
#line 305 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 968 "parsetl.cc"
    break;

  case 5: // result: "LTL start marker" emptyinput
#line 310 "parsetl.yy"
              { YYABORT; }
#line 974 "parsetl.cc"
    break;

  case 6: // result: "BOOLEAN start marker" boolformula "end of formula"
#line 312 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 983 "parsetl.cc"
    break;

  case 7: // result: "BOOLEAN start marker" enderror
#line 317 "parsetl.yy"
              {
		result = nullptr;
		YYABORT;
	      }
#line 992 "parsetl.cc"
    break;

  case 8: // result: "BOOLEAN start marker" boolformula enderror
#line 322 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 1001 "parsetl.cc"
    break;

  case 9: // result: "BOOLEAN start marker" emptyinput
#line 327 "parsetl.yy"
              { YYABORT; }
#line 1007 "parsetl.cc"
    break;

  case 10: // result: "SERE start marker" sere "end of formula"
#line 329 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 1016 "parsetl.cc"
    break;

  case 11: // result: "SERE start marker" enderror
#line 334 "parsetl.yy"
              {
		result = nullptr;
		YYABORT;
	      }
#line 1025 "parsetl.cc"
    break;

  case 12: // result: "SERE start marker" sere enderror
#line 339 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 1034 "parsetl.cc"
    break;

  case 13: // result: "SERE start marker" emptyinput
#line 344 "parsetl.yy"
              { YYABORT; }
#line 1040 "parsetl.cc"
    break;

  case 14: // result: "LBT start marker" lbtformula "end of formula"
#line 346 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 1049 "parsetl.cc"
    break;

  case 15: // result: "LBT start marker" enderror
#line 351 "parsetl.yy"
              {
		result = nullptr;
		YYABORT;
	      }
#line 1058 "parsetl.cc"
    break;

  case 16: // result: "LBT start marker" lbtformula enderror
#line 356 "parsetl.yy"
              {
		result = formula((yystack_[1].value.ltl));
		YYACCEPT;
	      }
#line 1067 "parsetl.cc"
    break;

  case 17: // result: "LBT start marker" emptyinput
#line 361 "parsetl.yy"
              { YYABORT; }
#line 1073 "parsetl.cc"
    break;

  case 18: // emptyinput: "end of formula"
#line 364 "parsetl.yy"
              {
		error_list.emplace_back(yylhs.location, "empty input");
		result = nullptr;
	      }
#line 1082 "parsetl.cc"
    break;

  case 19: // enderror: error "end of formula"
#line 370 "parsetl.yy"
              {
		error_list.emplace_back(yystack_[1].location, "ignoring trailing garbage");
	      }
#line 1090 "parsetl.cc"
    break;

  case 26: // sqbkt_num: "number for square bracket operator"
#line 382 "parsetl.yy"
         {
           if ((yystack_[0].value.num) >= fnode::unbounded())
             {
               auto max = fnode::unbounded() - 1;
               std::ostringstream s;
               s << (yystack_[0].value.num) << " exceeds maximum supported repetition ("
                 << max << ")";
               error_list.emplace_back(yystack_[0].location, s.str());
               (yylhs.value.num) = max;
             }
           else
             {
               (yylhs.value.num) = (yystack_[0].value.num);
             }
         }
#line 1110 "parsetl.cc"
    break;

  case 27: // sqbracketargs: sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket"
#line 400 "parsetl.yy"
              { (yylhs.value.minmax).min = (yystack_[3].value.num); (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1116 "parsetl.cc"
    break;

  case 28: // sqbracketargs: sqbkt_num OP_SQBKT_SEP_unbounded "closing bracket"
#line 402 "parsetl.yy"
              { (yylhs.value.minmax).min = (yystack_[2].value.num); (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1122 "parsetl.cc"
    break;

  case 29: // sqbracketargs: "separator for square bracket operator" sqbkt_num "closing bracket"
#line 404 "parsetl.yy"
              { (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1128 "parsetl.cc"
    break;

  case 30: // sqbracketargs: OP_SQBKT_SEP_opt "closing bracket"
#line 406 "parsetl.yy"
              { (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1134 "parsetl.cc"
    break;

  case 31: // sqbracketargs: sqbkt_num "closing bracket"
#line 408 "parsetl.yy"
              { (yylhs.value.minmax).min = (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1140 "parsetl.cc"
    break;

  case 32: // gotoargs: "opening bracket for goto operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket"
#line 412 "parsetl.yy"
           { (yylhs.value.minmax).min = (yystack_[3].value.num); (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1146 "parsetl.cc"
    break;

  case 33: // gotoargs: "opening bracket for goto operator" sqbkt_num OP_SQBKT_SEP_unbounded "closing bracket"
#line 414 "parsetl.yy"
           { (yylhs.value.minmax).min = (yystack_[2].value.num); (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1152 "parsetl.cc"
    break;

  case 34: // gotoargs: "opening bracket for goto operator" "separator for square bracket operator" sqbkt_num "closing bracket"
#line 416 "parsetl.yy"
           { (yylhs.value.minmax).min = 1U; (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1158 "parsetl.cc"
    break;

  case 35: // gotoargs: "opening bracket for goto operator" OP_SQBKT_SEP_unbounded "closing bracket"
#line 418 "parsetl.yy"
           { (yylhs.value.minmax).min = 1U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1164 "parsetl.cc"
    break;

  case 36: // gotoargs: "opening bracket for goto operator" "closing bracket"
#line 420 "parsetl.yy"
           { (yylhs.value.minmax).min = (yylhs.value.minmax).max = 1U; }
#line 1170 "parsetl.cc"
    break;

  case 37: // gotoargs: "opening bracket for goto operator" sqbkt_num "closing bracket"
#line 422 "parsetl.yy"
           { (yylhs.value.minmax).min = (yylhs.value.minmax).max = (yystack_[1].value.num); }
#line 1176 "parsetl.cc"
    break;

  case 38: // gotoargs: "opening bracket for goto operator" error "closing bracket"
#line 424 "parsetl.yy"
           { error_list.emplace_back(yylhs.location, "treating this goto block as [->]");
             (yylhs.value.minmax).min = (yylhs.value.minmax).max = 1U; }
#line 1183 "parsetl.cc"
    break;

  case 39: // gotoargs: "opening bracket for goto operator" error_opt "end of formula"
#line 427 "parsetl.yy"
           { error_list.
	       emplace_back(yylhs.location, "missing closing bracket for goto operator");
	     (yylhs.value.minmax).min = (yylhs.value.minmax).max = 0U; }
#line 1191 "parsetl.cc"
    break;

  case 42: // starargs: kleen_star
#line 434 "parsetl.yy"
            { (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1197 "parsetl.cc"
    break;

  case 43: // starargs: "plus operator"
#line 436 "parsetl.yy"
            { (yylhs.value.minmax).min = 1U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1203 "parsetl.cc"
    break;

  case 44: // starargs: "opening bracket for star operator" sqbracketargs
#line 438 "parsetl.yy"
            { (yylhs.value.minmax) = (yystack_[0].value.minmax); }
#line 1209 "parsetl.cc"
    break;

  case 45: // starargs: "opening bracket for star operator" error "closing bracket"
#line 440 "parsetl.yy"
            { error_list.emplace_back(yylhs.location, "treating this star block as [*]");
              (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1216 "parsetl.cc"
    break;

  case 46: // starargs: "opening bracket for star operator" error_opt "end of formula"
#line 443 "parsetl.yy"
            { error_list.emplace_back(yylhs.location, "missing closing bracket for star");
	      (yylhs.value.minmax).min = (yylhs.value.minmax).max = 0U; }
#line 1223 "parsetl.cc"
    break;

  case 47: // fstarargs: "bracket fusion-star operator"
#line 447 "parsetl.yy"
            { (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1229 "parsetl.cc"
    break;

  case 48: // fstarargs: "fusion-plus operator"
#line 449 "parsetl.yy"
            { (yylhs.value.minmax).min = 1U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1235 "parsetl.cc"
    break;

  case 49: // fstarargs: "opening bracket for fusion-star operator" sqbracketargs
#line 451 "parsetl.yy"
            { (yylhs.value.minmax) = (yystack_[0].value.minmax); }
#line 1241 "parsetl.cc"
    break;

  case 50: // fstarargs: "opening bracket for fusion-star operator" error "closing bracket"
#line 453 "parsetl.yy"
            { error_list.emplace_back
		(yylhs.location, "treating this fusion-star block as [:*]");
              (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1249 "parsetl.cc"
    break;

  case 51: // fstarargs: "opening bracket for fusion-star operator" error_opt "end of formula"
#line 457 "parsetl.yy"
            { error_list.emplace_back
		(yylhs.location, "missing closing bracket for fusion-star");
	      (yylhs.value.minmax).min = (yylhs.value.minmax).max = 0U; }
#line 1257 "parsetl.cc"
    break;

  case 52: // equalargs: "opening bracket for equal operator" sqbracketargs
#line 462 "parsetl.yy"
            { (yylhs.value.minmax) = (yystack_[0].value.minmax); }
#line 1263 "parsetl.cc"
    break;

  case 53: // equalargs: "opening bracket for equal operator" error "closing bracket"
#line 464 "parsetl.yy"
            { error_list.emplace_back(yylhs.location, "treating this equal block as [=]");
              (yylhs.value.minmax).min = 0U; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1270 "parsetl.cc"
    break;

  case 54: // equalargs: "opening bracket for equal operator" error_opt "end of formula"
#line 467 "parsetl.yy"
            { error_list.
		emplace_back(yylhs.location, "missing closing bracket for equal operator");
	      (yylhs.value.minmax).min = (yylhs.value.minmax).max = 0U; }
#line 1278 "parsetl.cc"
    break;

  case 55: // delayargs: "opening bracket for SVA delay operator" sqbracketargs
#line 472 "parsetl.yy"
            { (yylhs.value.minmax) = (yystack_[0].value.minmax); }
#line 1284 "parsetl.cc"
    break;

  case 56: // delayargs: "opening bracket for SVA delay operator" error "closing bracket"
#line 474 "parsetl.yy"
            { error_list.emplace_back(yylhs.location, "treating this delay block as ##1");
              (yylhs.value.minmax).min = (yylhs.value.minmax).max = 1U; }
#line 1291 "parsetl.cc"
    break;

  case 57: // delayargs: "opening bracket for SVA delay operator" error_opt "end of formula"
#line 477 "parsetl.yy"
            { error_list.
		emplace_back(yylhs.location, "missing closing bracket for ##[");
	      (yylhs.value.minmax).min = (yylhs.value.minmax).max = 1U; }
#line 1299 "parsetl.cc"
    break;

  case 58: // delayargs: "##[+] operator"
#line 481 "parsetl.yy"
          { (yylhs.value.minmax).min = 1; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1305 "parsetl.cc"
    break;

  case 59: // delayargs: "##[*] operator"
#line 483 "parsetl.yy"
          { (yylhs.value.minmax).min = 0; (yylhs.value.minmax).max = fnode::unbounded(); }
#line 1311 "parsetl.cc"
    break;

  case 60: // atomprop: "atomic proposition"
#line 486 "parsetl.yy"
          {
            (yylhs.value.ltl) = parse_ap(*(yystack_[0].value.str), yystack_[0].location, parse_environment, error_list);
            delete (yystack_[0].value.str);
            if (!(yylhs.value.ltl))
              YYERROR;
          }
#line 1322 "parsetl.cc"
    break;

  case 61: // booleanatom: atomprop
#line 493 "parsetl.yy"
             { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 1328 "parsetl.cc"
    break;

  case 62: // booleanatom: atomprop "positive suffix"
#line 494 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[1].value.ltl); }
#line 1334 "parsetl.cc"
    break;

  case 63: // booleanatom: atomprop "negative suffix"
#line 496 "parsetl.yy"
              {
		(yylhs.value.ltl) = fnode::unop(op::Not, (yystack_[1].value.ltl));
	      }
#line 1342 "parsetl.cc"
    break;

  case 64: // booleanatom: "constant true"
#line 500 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::tt(); }
#line 1348 "parsetl.cc"
    break;

  case 65: // booleanatom: "constant false"
#line 502 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::ff(); }
#line 1354 "parsetl.cc"
    break;

  case 66: // sere: booleanatom
#line 504 "parsetl.yy"
      { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 1360 "parsetl.cc"
    break;

  case 67: // sere: "not operator" sere
#line 506 "parsetl.yy"
              {
		if (sere_ensure_bool((yystack_[0].value.ltl), yystack_[0].location, "`!'", error_list))
		  {
		    (yylhs.value.ltl) = fnode::unop(op::Not, (yystack_[0].value.ltl));
		  }
		else
		  {
		    (yystack_[0].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1376 "parsetl.cc"
    break;

  case 68: // sere: bracedsere
#line 517 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 1382 "parsetl.cc"
    break;

  case 69: // sere: "(...) block"
#line 519 "parsetl.yy"
              {
		(yylhs.value.ltl) =
		  try_recursive_parse(*(yystack_[0].value.str), yystack_[0].location, parse_environment,
				      debug_level(), parser_sere, error_list);
		delete (yystack_[0].value.str);
		if (!(yylhs.value.ltl))
		  YYERROR;
	      }
#line 1395 "parsetl.cc"
    break;

  case 70: // sere: "opening parenthesis" sere "closing parenthesis"
#line 528 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[1].value.ltl); }
#line 1401 "parsetl.cc"
    break;

  case 71: // sere: "opening parenthesis" error "closing parenthesis"
#line 530 "parsetl.yy"
              { error_list.
		  emplace_back(yylhs.location,
			       "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1411 "parsetl.cc"
    break;

  case 72: // sere: "opening parenthesis" sere "end of formula"
#line 536 "parsetl.yy"
              { error_list.emplace_back(yystack_[2].location + yystack_[1].location, "missing closing parenthesis");
		(yylhs.value.ltl) = (yystack_[1].value.ltl);
	      }
#line 1419 "parsetl.cc"
    break;

  case 73: // sere: "opening parenthesis" error "end of formula"
#line 540 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
                    "missing closing parenthesis, "
		    "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1429 "parsetl.cc"
    break;

  case 74: // sere: sere "and operator" sere
#line 546 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::AndRat, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1435 "parsetl.cc"
    break;

  case 75: // sere: sere "and operator" error
#line 548 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
				    "length-matching and operator"); }
#line 1442 "parsetl.cc"
    break;

  case 76: // sere: sere "short and operator" sere
#line 551 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::AndNLM, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1448 "parsetl.cc"
    break;

  case 77: // sere: sere "short and operator" error
#line 553 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
                                    "non-length-matching and operator"); }
#line 1455 "parsetl.cc"
    break;

  case 78: // sere: sere "or operator" sere
#line 556 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::OrRat, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1461 "parsetl.cc"
    break;

  case 79: // sere: sere "or operator" error
#line 558 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "or operator"); }
#line 1467 "parsetl.cc"
    break;

  case 80: // sere: sere "concat operator" sere
#line 560 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::Concat, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1473 "parsetl.cc"
    break;

  case 81: // sere: sere "concat operator" error
#line 562 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "concat operator"); }
#line 1479 "parsetl.cc"
    break;

  case 82: // sere: sere "fusion operator" sere
#line 564 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::Fusion, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1485 "parsetl.cc"
    break;

  case 83: // sere: sere "fusion operator" error
#line 566 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "fusion operator"); }
#line 1491 "parsetl.cc"
    break;

  case 84: // sere: "SVA delay operator" sere
#line 568 "parsetl.yy"
              { (yylhs.value.ltl) = formula::sugar_delay(formula((yystack_[0].value.ltl)), (yystack_[1].value.num), (yystack_[1].value.num)).to_node_(); }
#line 1497 "parsetl.cc"
    break;

  case 85: // sere: "SVA delay operator" error
#line 570 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), fnode::tt(), yystack_[1].location, "SVA delay operator"); }
#line 1503 "parsetl.cc"
    break;

  case 86: // sere: sere "SVA delay operator" sere
#line 572 "parsetl.yy"
              { (yylhs.value.ltl) = formula::sugar_delay(formula((yystack_[2].value.ltl)), formula((yystack_[0].value.ltl)),
                                          (yystack_[1].value.num), (yystack_[1].value.num)).to_node_(); }
#line 1510 "parsetl.cc"
    break;

  case 87: // sere: sere "SVA delay operator" error
#line 575 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "SVA delay operator"); }
#line 1516 "parsetl.cc"
    break;

  case 88: // sere: delayargs sere
#line 577 "parsetl.yy"
              {
		if ((yystack_[1].value.minmax).max < (yystack_[1].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[1].location, "reversed range");
		    std::swap((yystack_[1].value.minmax).max, (yystack_[1].value.minmax).min);
		  }
                (yylhs.value.ltl) = formula::sugar_delay(formula((yystack_[0].value.ltl)),
                                          (yystack_[1].value.minmax).min, (yystack_[1].value.minmax).max).to_node_();
              }
#line 1530 "parsetl.cc"
    break;

  case 89: // sere: delayargs error
#line 587 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), fnode::tt(), yystack_[1].location, "SVA delay operator"); }
#line 1536 "parsetl.cc"
    break;

  case 90: // sere: sere delayargs sere
#line 589 "parsetl.yy"
              {
		if ((yystack_[1].value.minmax).max < (yystack_[1].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[2].location, "reversed range");
		    std::swap((yystack_[1].value.minmax).max, (yystack_[1].value.minmax).min);
		  }
                (yylhs.value.ltl) = formula::sugar_delay(formula((yystack_[2].value.ltl)), formula((yystack_[0].value.ltl)),
                                          (yystack_[1].value.minmax).min, (yystack_[1].value.minmax).max).to_node_();
              }
#line 1550 "parsetl.cc"
    break;

  case 91: // sere: sere delayargs error
#line 599 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "SVA delay operator"); }
#line 1556 "parsetl.cc"
    break;

  case 92: // sere: starargs
#line 601 "parsetl.yy"
              {
		if ((yystack_[0].value.minmax).max < (yystack_[0].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[0].location, "reversed range");
		    std::swap((yystack_[0].value.minmax).max, (yystack_[0].value.minmax).min);
		  }
		(yylhs.value.ltl) = fnode::bunop(op::Star, fnode::tt(), (yystack_[0].value.minmax).min, (yystack_[0].value.minmax).max);
	      }
#line 1569 "parsetl.cc"
    break;

  case 93: // sere: sere starargs
#line 610 "parsetl.yy"
              {
		if ((yystack_[0].value.minmax).max < (yystack_[0].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[0].location, "reversed range");
		    std::swap((yystack_[0].value.minmax).max, (yystack_[0].value.minmax).min);
		  }
		(yylhs.value.ltl) = fnode::bunop(op::Star, (yystack_[1].value.ltl), (yystack_[0].value.minmax).min, (yystack_[0].value.minmax).max);
	      }
#line 1582 "parsetl.cc"
    break;

  case 94: // sere: sere fstarargs
#line 619 "parsetl.yy"
              {
		if ((yystack_[0].value.minmax).max < (yystack_[0].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[0].location, "reversed range");
		    std::swap((yystack_[0].value.minmax).max, (yystack_[0].value.minmax).min);
		  }
		(yylhs.value.ltl) = fnode::bunop(op::FStar, (yystack_[1].value.ltl), (yystack_[0].value.minmax).min, (yystack_[0].value.minmax).max);
	      }
#line 1595 "parsetl.cc"
    break;

  case 95: // sere: sere equalargs
#line 628 "parsetl.yy"
              {
		if ((yystack_[0].value.minmax).max < (yystack_[0].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[0].location, "reversed range");
		    std::swap((yystack_[0].value.minmax).max, (yystack_[0].value.minmax).min);
		  }
		if (sere_ensure_bool((yystack_[1].value.ltl), yystack_[1].location, "[=...]", error_list))
		  {
		    (yylhs.value.ltl) = formula::sugar_equal(formula((yystack_[1].value.ltl)),
					      (yystack_[0].value.minmax).min, (yystack_[0].value.minmax).max).to_node_();
		  }
		else
		  {
		    (yystack_[1].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1617 "parsetl.cc"
    break;

  case 96: // sere: sere gotoargs
#line 646 "parsetl.yy"
              {
		if ((yystack_[0].value.minmax).max < (yystack_[0].value.minmax).min)
		  {
		    error_list.emplace_back(yystack_[0].location, "reversed range");
		    std::swap((yystack_[0].value.minmax).max, (yystack_[0].value.minmax).min);
		  }
		if (sere_ensure_bool((yystack_[1].value.ltl), yystack_[1].location, "[->...]", error_list))
		  {
		    (yylhs.value.ltl) = formula::sugar_goto(formula((yystack_[1].value.ltl)),
					     (yystack_[0].value.minmax).min, (yystack_[0].value.minmax).max).to_node_();
		  }
		else
		  {
		    (yystack_[1].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1639 "parsetl.cc"
    break;

  case 97: // sere: sere "xor operator" sere
#line 664 "parsetl.yy"
              {
		if (sere_ensure_bool((yystack_[2].value.ltl), yystack_[2].location, "`^'", error_list)
                    && sere_ensure_bool((yystack_[0].value.ltl), yystack_[0].location, "`^'", error_list))
		  {
		    (yylhs.value.ltl) = fnode::binop(op::Xor, (yystack_[2].value.ltl), (yystack_[0].value.ltl));
		  }
		else
		  {
		    (yystack_[2].value.ltl)->destroy();
		    (yystack_[0].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1657 "parsetl.cc"
    break;

  case 98: // sere: sere "xor operator" error
#line 678 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "xor operator"); }
#line 1663 "parsetl.cc"
    break;

  case 99: // sere: sere "implication operator" sere
#line 680 "parsetl.yy"
              {
		if (sere_ensure_bool((yystack_[2].value.ltl), yystack_[2].location, "`->'", error_list))
		  {
		    (yylhs.value.ltl) = fnode::binop(op::Implies, (yystack_[2].value.ltl), (yystack_[0].value.ltl));
		  }
		else
		  {
		    (yystack_[2].value.ltl)->destroy();
		    (yystack_[0].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1680 "parsetl.cc"
    break;

  case 100: // sere: sere "implication operator" error
#line 693 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "implication operator"); }
#line 1686 "parsetl.cc"
    break;

  case 101: // sere: sere "equivalent operator" sere
#line 695 "parsetl.yy"
              {
		if (sere_ensure_bool((yystack_[2].value.ltl), yystack_[2].location, "`<->'", error_list)
                    && sere_ensure_bool((yystack_[0].value.ltl), yystack_[0].location, "`<->'", error_list))
		  {
		    (yylhs.value.ltl) = fnode::binop(op::Equiv, (yystack_[2].value.ltl), (yystack_[0].value.ltl));
		  }
		else
		  {
		    (yystack_[2].value.ltl)->destroy();
		    (yystack_[0].value.ltl)->destroy();
		    (yylhs.value.ltl) = error_false_block(yylhs.location, error_list);
		  }
	      }
#line 1704 "parsetl.cc"
    break;

  case 102: // sere: sere "equivalent operator" error
#line 709 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "equivalent operator"); }
#line 1710 "parsetl.cc"
    break;

  case 103: // sere: "first_match" "opening parenthesis" sere "closing parenthesis"
#line 711 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::first_match, (yystack_[1].value.ltl)); }
#line 1716 "parsetl.cc"
    break;

  case 104: // bracedsere: "opening brace" sere "closing brace"
#line 714 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[1].value.ltl); }
#line 1722 "parsetl.cc"
    break;

  case 105: // bracedsere: "opening brace" sere error "closing brace"
#line 716 "parsetl.yy"
              { error_list.emplace_back(yystack_[1].location, "ignoring this");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1730 "parsetl.cc"
    break;

  case 106: // bracedsere: "opening brace" error "closing brace"
#line 720 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
					"treating this brace block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1739 "parsetl.cc"
    break;

  case 107: // bracedsere: "opening brace" sere "end of formula"
#line 725 "parsetl.yy"
              { error_list.emplace_back(yystack_[2].location + yystack_[1].location,
					"missing closing brace");
		(yylhs.value.ltl) = (yystack_[1].value.ltl);
	      }
#line 1748 "parsetl.cc"
    break;

  case 108: // bracedsere: "opening brace" sere error "end of formula"
#line 730 "parsetl.yy"
              { error_list. emplace_back(yystack_[1].location,
                  "ignoring trailing garbage and missing closing brace");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1757 "parsetl.cc"
    break;

  case 109: // bracedsere: "opening brace" error "end of formula"
#line 735 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
                    "missing closing brace, "
		    "treating this brace block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1767 "parsetl.cc"
    break;

  case 110: // bracedsere: "{...} block"
#line 741 "parsetl.yy"
              {
		(yylhs.value.ltl) = try_recursive_parse(*(yystack_[0].value.str), yystack_[0].location, parse_environment,
					 debug_level(),
                                         parser_sere, error_list);
		delete (yystack_[0].value.str);
		if (!(yylhs.value.ltl))
		  YYERROR;
	      }
#line 1780 "parsetl.cc"
    break;

  case 111: // parenthesedsubformula: "(...) block"
#line 751 "parsetl.yy"
              {
		(yylhs.value.ltl) = try_recursive_parse(*(yystack_[0].value.str), yystack_[0].location, parse_environment,
					 debug_level(), parser_ltl, error_list);
		delete (yystack_[0].value.str);
		if (!(yylhs.value.ltl))
		  YYERROR;
	      }
#line 1792 "parsetl.cc"
    break;

  case 112: // parenthesedsubformula: "opening parenthesis" subformula "closing parenthesis"
#line 759 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[1].value.ltl); }
#line 1798 "parsetl.cc"
    break;

  case 113: // parenthesedsubformula: "opening parenthesis" subformula error "closing parenthesis"
#line 761 "parsetl.yy"
              { error_list.emplace_back(yystack_[1].location, "ignoring this");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1806 "parsetl.cc"
    break;

  case 114: // parenthesedsubformula: "opening parenthesis" error "closing parenthesis"
#line 765 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
		 "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1815 "parsetl.cc"
    break;

  case 115: // parenthesedsubformula: "opening parenthesis" subformula "end of formula"
#line 770 "parsetl.yy"
              { error_list.emplace_back(yystack_[2].location + yystack_[1].location, "missing closing parenthesis");
		(yylhs.value.ltl) = (yystack_[1].value.ltl);
	      }
#line 1823 "parsetl.cc"
    break;

  case 116: // parenthesedsubformula: "opening parenthesis" subformula error "end of formula"
#line 774 "parsetl.yy"
              { error_list.emplace_back(yystack_[1].location,
                "ignoring trailing garbage and missing closing parenthesis");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1832 "parsetl.cc"
    break;

  case 117: // parenthesedsubformula: "opening parenthesis" error "end of formula"
#line 779 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
                    "missing closing parenthesis, "
		    "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1842 "parsetl.cc"
    break;

  case 118: // boolformula: booleanatom
#line 786 "parsetl.yy"
             { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 1848 "parsetl.cc"
    break;

  case 119: // boolformula: "(...) block"
#line 788 "parsetl.yy"
              {
		(yylhs.value.ltl) = try_recursive_parse(*(yystack_[0].value.str), yystack_[0].location, parse_environment,
					 debug_level(),
                                         parser_bool, error_list);
		delete (yystack_[0].value.str);
		if (!(yylhs.value.ltl))
		  YYERROR;
	      }
#line 1861 "parsetl.cc"
    break;

  case 120: // boolformula: "opening parenthesis" boolformula "closing parenthesis"
#line 797 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[1].value.ltl); }
#line 1867 "parsetl.cc"
    break;

  case 121: // boolformula: "opening parenthesis" boolformula error "closing parenthesis"
#line 799 "parsetl.yy"
              { error_list.emplace_back(yystack_[1].location, "ignoring this");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1875 "parsetl.cc"
    break;

  case 122: // boolformula: "opening parenthesis" error "closing parenthesis"
#line 803 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
		 "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1884 "parsetl.cc"
    break;

  case 123: // boolformula: "opening parenthesis" boolformula "end of formula"
#line 808 "parsetl.yy"
              { error_list.emplace_back(yystack_[2].location + yystack_[1].location,
					"missing closing parenthesis");
		(yylhs.value.ltl) = (yystack_[1].value.ltl);
	      }
#line 1893 "parsetl.cc"
    break;

  case 124: // boolformula: "opening parenthesis" boolformula error "end of formula"
#line 813 "parsetl.yy"
              { error_list.emplace_back(yystack_[1].location,
                "ignoring trailing garbage and missing closing parenthesis");
		(yylhs.value.ltl) = (yystack_[2].value.ltl);
	      }
#line 1902 "parsetl.cc"
    break;

  case 125: // boolformula: "opening parenthesis" error "end of formula"
#line 818 "parsetl.yy"
              { error_list.emplace_back(yylhs.location,
                    "missing closing parenthesis, "
		    "treating this parenthetical block as false");
		(yylhs.value.ltl) = fnode::ff();
	      }
#line 1912 "parsetl.cc"
    break;

  case 126: // boolformula: boolformula "and operator" boolformula
#line 824 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1918 "parsetl.cc"
    break;

  case 127: // boolformula: boolformula "and operator" error
#line 826 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 1924 "parsetl.cc"
    break;

  case 128: // boolformula: boolformula "short and operator" boolformula
#line 828 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1930 "parsetl.cc"
    break;

  case 129: // boolformula: boolformula "short and operator" error
#line 830 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 1936 "parsetl.cc"
    break;

  case 130: // boolformula: boolformula "star operator" boolformula
#line 832 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1942 "parsetl.cc"
    break;

  case 131: // boolformula: boolformula "star operator" error
#line 834 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 1948 "parsetl.cc"
    break;

  case 132: // boolformula: boolformula "or operator" boolformula
#line 836 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::Or, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 1954 "parsetl.cc"
    break;

  case 133: // boolformula: boolformula "or operator" error
#line 838 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "or operator"); }
#line 1960 "parsetl.cc"
    break;

  case 134: // boolformula: boolformula "xor operator" boolformula
#line 840 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Xor, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 1966 "parsetl.cc"
    break;

  case 135: // boolformula: boolformula "xor operator" error
#line 842 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "xor operator"); }
#line 1972 "parsetl.cc"
    break;

  case 136: // boolformula: boolformula "implication operator" boolformula
#line 844 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Implies, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 1978 "parsetl.cc"
    break;

  case 137: // boolformula: boolformula "implication operator" error
#line 846 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "implication operator"); }
#line 1984 "parsetl.cc"
    break;

  case 138: // boolformula: boolformula "equivalent operator" boolformula
#line 848 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Equiv, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 1990 "parsetl.cc"
    break;

  case 139: // boolformula: boolformula "equivalent operator" error
#line 850 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "equivalent operator"); }
#line 1996 "parsetl.cc"
    break;

  case 140: // boolformula: "not operator" boolformula
#line 852 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::Not, (yystack_[0].value.ltl)); }
#line 2002 "parsetl.cc"
    break;

  case 141: // boolformula: "not operator" error
#line 854 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "not operator"); }
#line 2008 "parsetl.cc"
    break;

  case 142: // subformula: booleanatom
#line 856 "parsetl.yy"
            { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 2014 "parsetl.cc"
    break;

  case 143: // subformula: parenthesedsubformula
#line 857 "parsetl.yy"
              { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 2020 "parsetl.cc"
    break;

  case 144: // subformula: subformula "and operator" subformula
#line 859 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 2026 "parsetl.cc"
    break;

  case 145: // subformula: subformula "and operator" error
#line 861 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 2032 "parsetl.cc"
    break;

  case 146: // subformula: subformula "short and operator" subformula
#line 863 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 2038 "parsetl.cc"
    break;

  case 147: // subformula: subformula "short and operator" error
#line 865 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 2044 "parsetl.cc"
    break;

  case 148: // subformula: subformula "star operator" subformula
#line 867 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 2050 "parsetl.cc"
    break;

  case 149: // subformula: subformula "star operator" error
#line 869 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "and operator"); }
#line 2056 "parsetl.cc"
    break;

  case 150: // subformula: subformula "or operator" subformula
#line 871 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::Or, {(yystack_[2].value.ltl), (yystack_[0].value.ltl)}); }
#line 2062 "parsetl.cc"
    break;

  case 151: // subformula: subformula "or operator" error
#line 873 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "or operator"); }
#line 2068 "parsetl.cc"
    break;

  case 152: // subformula: subformula "xor operator" subformula
#line 875 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Xor, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2074 "parsetl.cc"
    break;

  case 153: // subformula: subformula "xor operator" error
#line 877 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "xor operator"); }
#line 2080 "parsetl.cc"
    break;

  case 154: // subformula: subformula "implication operator" subformula
#line 879 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Implies, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2086 "parsetl.cc"
    break;

  case 155: // subformula: subformula "implication operator" error
#line 881 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "implication operator"); }
#line 2092 "parsetl.cc"
    break;

  case 156: // subformula: subformula "equivalent operator" subformula
#line 883 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Equiv, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2098 "parsetl.cc"
    break;

  case 157: // subformula: subformula "equivalent operator" error
#line 885 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "equivalent operator"); }
#line 2104 "parsetl.cc"
    break;

  case 158: // subformula: subformula "until operator" subformula
#line 887 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::U, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2110 "parsetl.cc"
    break;

  case 159: // subformula: subformula "until operator" error
#line 889 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "until operator"); }
#line 2116 "parsetl.cc"
    break;

  case 160: // subformula: subformula "release operator" subformula
#line 891 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::R, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2122 "parsetl.cc"
    break;

  case 161: // subformula: subformula "release operator" error
#line 893 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "release operator"); }
#line 2128 "parsetl.cc"
    break;

  case 162: // subformula: subformula "weak until operator" subformula
#line 895 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::W, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2134 "parsetl.cc"
    break;

  case 163: // subformula: subformula "weak until operator" error
#line 897 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "weak until operator"); }
#line 2140 "parsetl.cc"
    break;

  case 164: // subformula: subformula "strong release operator" subformula
#line 899 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::M, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2146 "parsetl.cc"
    break;

  case 165: // subformula: subformula "strong release operator" error
#line 901 "parsetl.yy"
              { missing_right_binop((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location, "strong release operator"); }
#line 2152 "parsetl.cc"
    break;

  case 166: // subformula: "sometimes operator" subformula
#line 903 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2158 "parsetl.cc"
    break;

  case 167: // subformula: "sometimes operator" error
#line 905 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "sometimes operator"); }
#line 2164 "parsetl.cc"
    break;

  case 168: // subformula: "F[.] operator" sqbkt_num "closing bracket" subformula
#line 907 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::Or, (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl));
                error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "F[n:m] expects two parameters");
              }
#line 2173 "parsetl.cc"
    break;

  case 169: // subformula: "F[.] operator" sqbkt_num "closing !]" subformula
#line 913 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X, op::Or, (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl));
                error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "F[n:m!] expects two parameters");
              }
#line 2182 "parsetl.cc"
    break;

  case 170: // subformula: "F[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket" subformula
#line 919 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::Or, (yystack_[4].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2188 "parsetl.cc"
    break;

  case 171: // subformula: "F[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing !]" subformula
#line 922 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X,
                                              op::Or, (yystack_[4].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2195 "parsetl.cc"
    break;

  case 172: // subformula: "F[.] operator" sqbkt_num OP_SQBKT_SEP_unbounded "closing bracket" subformula
#line 926 "parsetl.yy"
            { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::Or, (yystack_[3].value.num),
                                            fnode::unbounded(), (yystack_[0].value.ltl)); }
#line 2202 "parsetl.cc"
    break;

  case 173: // subformula: "F[.] operator" sqbkt_num OP_SQBKT_SEP_unbounded "closing !]" subformula
#line 930 "parsetl.yy"
            { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X, op::Or, (yystack_[3].value.num),
                                            fnode::unbounded(), (yystack_[0].value.ltl)); }
#line 2209 "parsetl.cc"
    break;

  case 174: // subformula: "F[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket" error
#line 934 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[5].location + yystack_[1].location, "F[.] operator"); }
#line 2215 "parsetl.cc"
    break;

  case 175: // subformula: "F[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing !]" error
#line 937 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[5].location + yystack_[1].location, "F[.!] operator"); }
#line 2221 "parsetl.cc"
    break;

  case 176: // subformula: "F[.] operator" error_opt "end of formula"
#line 939 "parsetl.yy"
              { error_list.emplace_back(yylhs.location, "missing closing bracket for F[.]");
                (yylhs.value.ltl) = fnode::ff(); }
#line 2228 "parsetl.cc"
    break;

  case 177: // subformula: "F[.] operator" error "closing bracket" subformula
#line 942 "parsetl.yy"
              { error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "treating this F[.] as a simple F");
                (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2236 "parsetl.cc"
    break;

  case 178: // subformula: "F[.] operator" error "closing !]" subformula
#line 946 "parsetl.yy"
              { error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "treating this F[.!] as a simple F");
                (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2244 "parsetl.cc"
    break;

  case 179: // subformula: "always operator" subformula
#line 950 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::G, (yystack_[0].value.ltl)); }
#line 2250 "parsetl.cc"
    break;

  case 180: // subformula: "always operator" error
#line 952 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "always operator"); }
#line 2256 "parsetl.cc"
    break;

  case 181: // subformula: "G[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket" subformula
#line 955 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::And, (yystack_[4].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2262 "parsetl.cc"
    break;

  case 182: // subformula: "G[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing !]" subformula
#line 958 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X, op::And,
                                              (yystack_[4].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2269 "parsetl.cc"
    break;

  case 183: // subformula: "G[.] operator" sqbkt_num OP_SQBKT_SEP_unbounded "closing bracket" subformula
#line 962 "parsetl.yy"
            { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::And, (yystack_[3].value.num),
                                            fnode::unbounded(), (yystack_[0].value.ltl)); }
#line 2276 "parsetl.cc"
    break;

  case 184: // subformula: "G[.] operator" sqbkt_num OP_SQBKT_SEP_unbounded "closing !]" subformula
#line 966 "parsetl.yy"
            { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X, op::And, (yystack_[3].value.num),
                                            fnode::unbounded(), (yystack_[0].value.ltl)); }
#line 2283 "parsetl.cc"
    break;

  case 185: // subformula: "G[.] operator" sqbkt_num "closing bracket" subformula
#line 969 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::And, (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl));
                error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "G[n:m] expects two parameters");
              }
#line 2292 "parsetl.cc"
    break;

  case 186: // subformula: "G[.] operator" sqbkt_num "closing !]" subformula
#line 975 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X, op::And,
                                              (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl));
                error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "G[n:m!] expects two parameters");
              }
#line 2302 "parsetl.cc"
    break;

  case 187: // subformula: "G[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing bracket" error
#line 982 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[5].location + yystack_[1].location, "G[.] operator"); }
#line 2308 "parsetl.cc"
    break;

  case 188: // subformula: "G[.] operator" sqbkt_num "separator for square bracket operator" sqbkt_num "closing !]" error
#line 985 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[5].location + yystack_[1].location, "G[.!] operator"); }
#line 2314 "parsetl.cc"
    break;

  case 189: // subformula: "G[.] operator" error_opt "end of formula"
#line 987 "parsetl.yy"
              { error_list.emplace_back(yylhs.location, "missing closing bracket for G[.]");
                (yylhs.value.ltl) = fnode::ff(); }
#line 2321 "parsetl.cc"
    break;

  case 190: // subformula: "G[.] operator" error "closing bracket" subformula
#line 990 "parsetl.yy"
              { error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "treating this G[.] as a simple G");
                (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2329 "parsetl.cc"
    break;

  case 191: // subformula: "G[.] operator" error "closing !]" subformula
#line 994 "parsetl.yy"
              { error_list.emplace_back(yystack_[3].location + yystack_[1].location,
                                        "treating this G[.!] as a simple G");
                (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2337 "parsetl.cc"
    break;

  case 192: // subformula: "next operator" subformula
#line 998 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::X, (yystack_[0].value.ltl)); }
#line 2343 "parsetl.cc"
    break;

  case 193: // subformula: "next operator" error
#line 1000 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "next operator"); }
#line 2349 "parsetl.cc"
    break;

  case 194: // subformula: "strong next operator" subformula
#line 1002 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::strong_X, (yystack_[0].value.ltl)); }
#line 2355 "parsetl.cc"
    break;

  case 195: // subformula: "strong next operator" error
#line 1004 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "strong next operator"); }
#line 2361 "parsetl.cc"
    break;

  case 196: // subformula: "X[.] operator" sqbkt_num "closing bracket" subformula
#line 1006 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::X, op::Or, (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2367 "parsetl.cc"
    break;

  case 197: // subformula: "X[.] operator" sqbkt_num "closing bracket" error
#line 1008 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[3].location + yystack_[1].location, "X[.] operator"); }
#line 2373 "parsetl.cc"
    break;

  case 198: // subformula: "X[.] operator" error "closing bracket" subformula
#line 1010 "parsetl.yy"
              { error_list.emplace_back(yylhs.location, "treating this X[.] as a simple X");
                (yylhs.value.ltl) = fnode::unop(op::X, (yystack_[0].value.ltl)); }
#line 2380 "parsetl.cc"
    break;

  case 199: // subformula: "X[.] operator" "closing !]" subformula
#line 1013 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::strong_X, (yystack_[0].value.ltl)); }
#line 2386 "parsetl.cc"
    break;

  case 200: // subformula: "X[.] operator" sqbkt_num "closing !]" subformula
#line 1016 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::nested_unop_range(op::strong_X,
                                              op::Or, (yystack_[2].value.num), (yystack_[2].value.num), (yystack_[0].value.ltl)); }
#line 2393 "parsetl.cc"
    break;

  case 201: // subformula: "X[.] operator" error "closing !]" subformula
#line 1019 "parsetl.yy"
              { error_list.emplace_back(yylhs.location, "treating this X[.!] as a simple X[!]");
                (yylhs.value.ltl) = fnode::unop(op::strong_X, (yystack_[0].value.ltl)); }
#line 2400 "parsetl.cc"
    break;

  case 202: // subformula: "X[.] operator" error_opt "end of formula"
#line 1022 "parsetl.yy"
              { error_list.emplace_back(yylhs.location, "missing closing bracket for X[.]");
                (yylhs.value.ltl) = fnode::ff(); }
#line 2407 "parsetl.cc"
    break;

  case 203: // subformula: "not operator" subformula
#line 1025 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::Not, (yystack_[0].value.ltl)); }
#line 2413 "parsetl.cc"
    break;

  case 204: // subformula: "not operator" error
#line 1027 "parsetl.yy"
              { missing_right_op((yylhs.value.ltl), yystack_[1].location, "not operator"); }
#line 2419 "parsetl.cc"
    break;

  case 205: // subformula: bracedsere
#line 1029 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::Closure, (yystack_[0].value.ltl)); }
#line 2425 "parsetl.cc"
    break;

  case 206: // subformula: bracedsere "universal concat operator" subformula
#line 1031 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::UConcat, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2431 "parsetl.cc"
    break;

  case 207: // subformula: bracedsere parenthesedsubformula
#line 1033 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::UConcat, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2437 "parsetl.cc"
    break;

  case 208: // subformula: bracedsere "universal concat operator" error
#line 1035 "parsetl.yy"
              { missing_right_binop_hard((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
				    "universal overlapping concat operator"); }
#line 2444 "parsetl.cc"
    break;

  case 209: // subformula: bracedsere "existential concat operator" subformula
#line 1038 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::EConcat, (yystack_[2].value.ltl), (yystack_[0].value.ltl)); }
#line 2450 "parsetl.cc"
    break;

  case 210: // subformula: bracedsere "existential concat operator" error
#line 1040 "parsetl.yy"
              { missing_right_binop_hard((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
				    "existential overlapping concat operator");
	      }
#line 2458 "parsetl.cc"
    break;

  case 211: // subformula: bracedsere "universal non-overlapping concat operator" subformula
#line 1045 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::UConcat,
				  fnode::multop(op::Concat, {(yystack_[2].value.ltl), fnode::tt()}),
				  (yystack_[0].value.ltl)); }
#line 2466 "parsetl.cc"
    break;

  case 212: // subformula: bracedsere "universal non-overlapping concat operator" error
#line 1049 "parsetl.yy"
              { missing_right_binop_hard((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
				  "universal non-overlapping concat operator");
	      }
#line 2474 "parsetl.cc"
    break;

  case 213: // subformula: bracedsere "existential non-overlapping concat operator" subformula
#line 1054 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::EConcat,
				  fnode::multop(op::Concat, {(yystack_[2].value.ltl), fnode::tt()}),
				  (yystack_[0].value.ltl)); }
#line 2482 "parsetl.cc"
    break;

  case 214: // subformula: bracedsere "existential non-overlapping concat operator" error
#line 1058 "parsetl.yy"
              { missing_right_binop_hard((yylhs.value.ltl), (yystack_[2].value.ltl), yystack_[1].location,
				"existential non-overlapping concat operator");
	      }
#line 2490 "parsetl.cc"
    break;

  case 215: // subformula: "opening brace" sere "closing brace-bang"
#line 1063 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::EConcat, (yystack_[1].value.ltl), fnode::tt()); }
#line 2496 "parsetl.cc"
    break;

  case 216: // subformula: "{...}! block"
#line 1065 "parsetl.yy"
              {
		(yylhs.value.ltl) = try_recursive_parse(*(yystack_[0].value.str), yystack_[0].location, parse_environment,
					 debug_level(),
                                         parser_sere, error_list);
		delete (yystack_[0].value.str);
		if (!(yylhs.value.ltl))
		  YYERROR;
		(yylhs.value.ltl) = fnode::binop(op::EConcat, (yylhs.value.ltl), fnode::tt());
	      }
#line 2510 "parsetl.cc"
    break;

  case 217: // lbtformula: atomprop
#line 1075 "parsetl.yy"
            { (yylhs.value.ltl) = (yystack_[0].value.ltl); }
#line 2516 "parsetl.cc"
    break;

  case 218: // lbtformula: '!' lbtformula
#line 1077 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::Not, (yystack_[0].value.ltl)); }
#line 2522 "parsetl.cc"
    break;

  case 219: // lbtformula: '&' lbtformula lbtformula
#line 1079 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::And, {(yystack_[1].value.ltl), (yystack_[0].value.ltl)}); }
#line 2528 "parsetl.cc"
    break;

  case 220: // lbtformula: '|' lbtformula lbtformula
#line 1081 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::multop(op::Or, {(yystack_[1].value.ltl), (yystack_[0].value.ltl)}); }
#line 2534 "parsetl.cc"
    break;

  case 221: // lbtformula: '^' lbtformula lbtformula
#line 1083 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Xor, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2540 "parsetl.cc"
    break;

  case 222: // lbtformula: 'i' lbtformula lbtformula
#line 1085 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Implies, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2546 "parsetl.cc"
    break;

  case 223: // lbtformula: 'e' lbtformula lbtformula
#line 1087 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::Equiv, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2552 "parsetl.cc"
    break;

  case 224: // lbtformula: 'X' lbtformula
#line 1089 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::X, (yystack_[0].value.ltl)); }
#line 2558 "parsetl.cc"
    break;

  case 225: // lbtformula: 'F' lbtformula
#line 1091 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::F, (yystack_[0].value.ltl)); }
#line 2564 "parsetl.cc"
    break;

  case 226: // lbtformula: 'G' lbtformula
#line 1093 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::unop(op::G, (yystack_[0].value.ltl)); }
#line 2570 "parsetl.cc"
    break;

  case 227: // lbtformula: 'U' lbtformula lbtformula
#line 1095 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::U, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2576 "parsetl.cc"
    break;

  case 228: // lbtformula: 'V' lbtformula lbtformula
#line 1097 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::R, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2582 "parsetl.cc"
    break;

  case 229: // lbtformula: 'R' lbtformula lbtformula
#line 1099 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::R, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2588 "parsetl.cc"
    break;

  case 230: // lbtformula: 'W' lbtformula lbtformula
#line 1101 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::W, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2594 "parsetl.cc"
    break;

  case 231: // lbtformula: 'M' lbtformula lbtformula
#line 1103 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::binop(op::M, (yystack_[1].value.ltl), (yystack_[0].value.ltl)); }
#line 2600 "parsetl.cc"
    break;

  case 232: // lbtformula: 't'
#line 1105 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::tt(); }
#line 2606 "parsetl.cc"
    break;

  case 233: // lbtformula: 'f'
#line 1107 "parsetl.yy"
              { (yylhs.value.ltl) = fnode::ff(); }
#line 2612 "parsetl.cc"
    break;


#line 2616 "parsetl.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -88;

  const signed char parser::yytable_ninf_ = -25;

  const short
  parser::yypact_[] =
  {
     304,   556,   385,   593,   129,     4,   -38,  1308,   -88,   -88,
     -88,   629,  1345,  1377,  1409,  1441,  1473,    42,   138,   170,
     -88,   -88,   -88,   -88,   -88,   -88,    91,   -88,   269,   -88,
    1206,  2242,  2242,  2242,  2242,  2242,  2242,  2242,  2242,  2242,
    2242,  2242,  2242,  2242,  2242,   -88,   -88,   -88,   -88,   -88,
       0,   665,   -88,   629,  1132,   -88,   -88,   -88,   150,    19,
     701,   182,   -88,   -88,   -88,   -88,   -88,   -88,   737,   -88,
     536,   -88,   297,   -88,   388,   -88,   -88,   -88,    34,   -88,
     -88,     2,  1181,    12,   471,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   114,  2188,   -88,   -28,   117,
     145,   -20,   -19,   155,     3,   -10,   -88,   -88,  1505,  1537,
    1569,  1601,   -88,  1633,  1665,  1697,  1729,  1761,  1793,  1825,
    1857,  1889,  1921,  1953,   -88,   -88,   -88,  2242,  2242,  2242,
    2242,  2242,   -88,   -88,   -88,  2242,  2242,  2242,  2242,  2242,
     -88,   -88,     6,  1238,   482,   -88,   -11,   157,   -88,    -8,
       5,    48,   -88,  1132,   -88,  2307,    23,    35,   -88,   -88,
    2307,   773,   809,   845,   881,   917,   953,   -88,   -88,   188,
     189,   235,   989,  1025,   -88,  1061,   -88,   -88,   -88,   -88,
     -88,  1097,     9,  1232,   -88,   -88,  1082,  2120,  2125,  2149,
    2154,  2178,  2183,   -88,   -88,   -88,   -88,    30,   -88,   -88,
     -88,   -88,    43,   -88,   -88,   -88,  2188,  2188,   -88,   -88,
    1985,  2188,  2188,  2188,   -88,  2188,  2188,   157,   207,  2188,
    2188,   -88,  2188,  2188,   157,   211,   -88,  2343,   -88,  2343,
     -88,  2343,   -88,  2343,   -88,  1264,   -88,  2204,   -88,   279,
     -88,   279,   -88,  2343,   -88,  2343,   -88,   251,   -88,   251,
     -88,   251,   -88,   251,   -88,   251,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,    56,   -88,   -88,   -88,   157,    63,  1288,   -88,
     -88,   -88,  1138,   -88,  2316,   -88,  2344,   -88,  2344,   -88,
    2307,   -88,  2307,    81,    74,   -88,    93,    76,   -88,    98,
     -88,   157,   110,   104,    51,   -88,  2230,   -88,  2239,   -88,
    2307,   -88,  2307,   -88,   -88,    38,   -88,   -88,   -88,   146,
     -88,    22,   -88,   158,   -88,   158,   -88,   599,   -88,   599,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   281,  2188,  2188,   -88,   -88,
     -88,   -88,   294,  2188,  2188,   -88,   151,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   168,   -88,   -88,   -88,   157,   177,
     -88,   -88,  2017,  2049,   -88,   -88,  2081,  2113,   -88,   -88,
     -88,   -88,   179,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,   111,   110,
     216,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    64,    65,    18,     5,     3,    61,   142,   205,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   232,   233,    17,    15,   217,
       0,     0,    69,     0,     0,    40,    41,    43,     0,     0,
       0,     0,    58,    59,    13,    11,    42,    92,     0,    66,
       0,    68,     0,   119,     0,     9,     7,   118,     0,     1,
      19,     0,     0,     0,     0,   167,   166,   180,   179,   193,
     192,   195,   194,   204,   203,    25,     0,    26,     0,     0,
      25,     0,     0,    25,     0,     0,    63,    62,     0,     0,
       0,     0,   207,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     4,   218,     0,     0,     0,
       0,     0,   224,   225,   226,     0,     0,     0,     0,     0,
      14,    16,     0,     0,     0,    67,    25,    20,    23,     0,
       0,     0,    44,     0,    85,    84,    25,     0,    55,    89,
      88,     0,     0,     0,     0,     0,     0,    47,    48,     0,
       0,     0,     0,     0,    10,     0,    12,    96,    93,    94,
      95,     0,     0,     0,   141,   140,     0,     0,     0,     0,
       0,     0,     0,     6,     8,   114,   117,     0,   112,   115,
     106,   109,     0,   104,   215,   107,     0,     0,   199,   202,
       0,     0,     0,     0,   176,     0,     0,    20,     0,     0,
       0,   189,     0,     0,    20,     0,   208,   206,   210,   209,
     212,   211,   214,   213,   151,   150,   153,   152,   145,   144,
     147,   146,   155,   154,   157,   156,   159,   158,   161,   160,
     163,   162,   165,   164,   149,   148,   219,   220,   221,   222,
     223,   227,   228,   229,   230,   231,    71,    73,    70,    72,
      45,    21,     0,    30,    46,    31,    20,     0,     0,    56,
      57,    79,    78,    98,    97,    75,    74,    77,    76,   100,
      99,   102,   101,    25,     0,    49,    25,     0,    52,    25,
      36,    20,     0,     0,     0,    81,    80,    83,    82,    87,
      86,    91,    90,   122,   125,     0,   120,   123,   133,   132,
     135,   134,   127,   126,   129,   128,   137,   136,   139,   138,
     131,   130,   113,   116,   105,   108,   198,   201,   197,   196,
     200,   177,   178,   168,   169,     0,     0,     0,   190,   191,
     185,   186,     0,     0,     0,    29,     0,    28,   103,    50,
      51,    53,    54,    38,     0,    35,    39,    37,    20,     0,
     121,   124,     0,     0,   172,   173,     0,     0,   183,   184,
      27,    34,     0,    33,   174,   170,   175,   171,   187,   181,
     188,   182,    32
  };

  const short
  parser::yypgoto_[] =
  {
     -88,   -88,   124,    18,   -87,   -88,   -16,    -6,   -45,   -88,
     -88,   -26,   -88,   -88,   -23,    39,   169,   260,   237,   197,
     -44,    -7,   340
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     5,    24,    25,   148,   149,    98,   151,   152,   177,
      66,    67,   179,   180,    68,    26,    27,    70,    28,    29,
      78,    30,    50
  };

  const short
  parser::yytable_[] =
  {
      82,     6,   101,   104,    79,    86,    88,    90,    92,    94,
     195,    99,   102,   105,   266,   218,   158,   313,   225,    80,
      48,    65,    76,   215,   216,   200,   153,   217,   183,   209,
     185,   270,   222,   223,   273,     6,   224,   214,   332,   188,
     189,    49,   150,    95,   178,   157,   370,   181,   125,   186,
     187,   188,   189,   190,   191,   192,   334,   140,   178,   196,
     221,   181,   274,   267,   277,   279,   314,   192,   141,   201,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,   302,    96,    97,   333,   176,   208,
     275,   193,   280,   367,   276,   371,   194,   368,   355,   -24,
     335,   227,   229,   231,   233,   357,   235,   237,   239,   241,
     243,   245,   247,   249,   251,   253,   255,   178,   178,   178,
     181,   181,   181,   359,   295,   298,    47,    64,    75,   178,
       6,   360,   181,   362,   178,   361,    72,   181,    73,   100,
     363,   272,   319,   321,   323,   325,   327,   329,   331,   106,
     107,   146,   365,   294,   297,   303,   206,   207,    74,   210,
     211,   366,   187,   188,   189,   304,    49,    49,    49,    49,
      49,   103,    69,    77,    49,    49,    49,    49,    49,   192,
      69,    20,    97,   156,    21,    22,    23,   212,   213,   293,
     296,   192,   -22,   380,    97,   -24,   147,   219,   220,   336,
     337,    97,   271,   339,   340,   341,   342,   -24,   343,   344,
     381,   345,   348,   349,    97,   350,   351,   369,   352,   383,
      69,   392,    69,    69,   -22,   112,    97,   -24,   147,    69,
     -22,   -22,    97,    97,   147,   147,   299,    69,     0,   -24,
      71,    77,     0,    77,     0,   -24,   -24,     0,    71,   346,
     347,     0,   178,   353,   354,   181,   178,     0,   178,   181,
     178,   181,   178,   181,   178,   181,   178,   181,     0,   181,
     356,    84,   119,   120,   121,   122,     7,   300,     8,    97,
     178,   301,   178,   181,   178,   181,   178,   181,    71,   181,
      71,    71,   -24,     0,     0,   364,     0,    71,   182,     0,
     119,   120,   121,   122,    72,    71,    73,     1,     2,     3,
       4,   143,   123,   144,   145,     0,   108,   109,   110,   111,
     155,     0,    69,   372,   373,     0,    74,     0,   160,     0,
      69,    69,    69,    69,    69,    69,   376,   377,     0,   374,
     375,    69,    69,     0,    69,     0,   378,   379,     0,    20,
      69,     0,    21,    22,     0,    77,    77,    77,    77,    77,
      77,    77,   382,     0,     0,   385,   387,     0,     0,   389,
     391,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,     6,     0,     0,   184,
      71,     0,     0,     0,     0,    72,     0,    73,    71,    71,
      71,    71,    71,    71,     0,     0,     0,     0,     0,    71,
      71,     0,    71,   278,     0,     0,     0,    74,    71,     0,
       0,   282,   284,   286,   288,   290,   292,     0,     0,     0,
       0,     0,   306,   308,     0,   310,     0,    20,     0,     0,
      20,   312,    23,    21,    22,     0,     0,     0,     0,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,     0,     0,   256,   257,   258,
     259,   260,   202,     0,     0,   261,   262,   263,   264,   265,
       0,     0,     0,   202,   203,   204,   161,   162,   163,   164,
     165,   166,     0,     0,     0,   203,     0,   161,   162,   163,
     164,   165,   166,     0,    55,    56,   167,    57,   168,    58,
     169,   170,   171,     0,     0,    55,    56,   167,    57,   168,
      58,   169,   170,   171,   172,   173,     0,     0,   205,     0,
       0,   175,    61,    62,    63,   172,   173,     6,     0,   205,
       0,     0,   175,    61,    62,    63,     0,     0,     0,     0,
       0,   161,   162,   163,   164,   165,   166,     6,     0,     0,
       0,     0,     0,     7,     0,     8,     9,    10,    11,    55,
      56,   167,    57,   168,    58,   169,   170,   171,     0,     0,
       0,    12,    13,    14,    15,    16,    17,    18,    19,   172,
     173,     0,     0,   174,     6,     0,   175,    61,    62,    63,
      51,     0,    52,     9,     0,    53,     0,     0,    20,     0,
       0,    21,    22,    23,   186,   187,   188,   189,   190,   191,
       0,     0,    54,     0,     0,     0,    55,    56,     0,    57,
      83,    58,   192,     0,     0,     0,    51,     0,    52,     9,
       0,    53,     0,     0,    59,    20,     0,     0,    21,    22,
      23,     0,     0,    60,    61,    62,    63,     0,    54,     0,
       0,     0,    55,    56,     0,    57,   142,    58,     0,     0,
       0,     0,    51,     0,    52,     9,     0,    53,     0,     0,
      59,    20,     0,     0,    21,    22,     0,     0,     0,    60,
      61,    62,    63,     0,    54,     0,     0,     0,    55,    56,
       0,    57,   154,    58,     0,     0,     0,     0,    51,     0,
      52,     9,     0,    53,     0,     0,    59,    20,     0,     0,
      21,    22,     0,     0,     0,    60,    61,    62,    63,     0,
      54,     0,     0,     0,    55,    56,     0,    57,   159,    58,
       0,     0,     0,     0,    51,     0,    52,     9,     0,    53,
       0,     0,    59,    20,     0,     0,    21,    22,     0,     0,
       0,    60,    61,    62,    63,     0,    54,     0,     0,     0,
      55,    56,     0,    57,   281,    58,     0,     0,     0,     0,
      51,     0,    52,     9,     0,    53,     0,     0,    59,    20,
       0,     0,    21,    22,     0,     0,     0,    60,    61,    62,
      63,     0,    54,     0,     0,     0,    55,    56,     0,    57,
     283,    58,     0,     0,     0,     0,    51,     0,    52,     9,
       0,    53,     0,     0,    59,    20,     0,     0,    21,    22,
       0,     0,     0,    60,    61,    62,    63,     0,    54,     0,
       0,     0,    55,    56,     0,    57,   285,    58,     0,     0,
       0,     0,    51,     0,    52,     9,     0,    53,     0,     0,
      59,    20,     0,     0,    21,    22,     0,     0,     0,    60,
      61,    62,    63,     0,    54,     0,     0,     0,    55,    56,
       0,    57,   287,    58,     0,     0,     0,     0,    51,     0,
      52,     9,     0,    53,     0,     0,    59,    20,     0,     0,
      21,    22,     0,     0,     0,    60,    61,    62,    63,     0,
      54,     0,     0,     0,    55,    56,     0,    57,   289,    58,
       0,     0,     0,     0,    51,     0,    52,     9,     0,    53,
       0,     0,    59,    20,     0,     0,    21,    22,     0,     0,
       0,    60,    61,    62,    63,     0,    54,     0,     0,     0,
      55,    56,     0,    57,   291,    58,     0,     0,     0,     0,
      51,     0,    52,     9,     0,    53,     0,     0,    59,    20,
       0,     0,    21,    22,     0,     0,     0,    60,    61,    62,
      63,     0,    54,     0,     0,     0,    55,    56,     0,    57,
     305,    58,     0,     0,     0,     0,    51,     0,    52,     9,
       0,    53,     0,     0,    59,    20,     0,     0,    21,    22,
       0,     0,     0,    60,    61,    62,    63,     0,    54,     0,
       0,     0,    55,    56,     0,    57,   307,    58,     0,     0,
       0,     0,    51,     0,    52,     9,     0,    53,     0,     0,
      59,    20,     0,     0,    21,    22,     0,     0,     0,    60,
      61,    62,    63,     0,    54,     0,     0,     0,    55,    56,
       0,    57,   309,    58,     0,     0,     0,     0,    51,     0,
      52,     9,     0,    53,     0,     0,    59,    20,     0,     0,
      21,    22,     0,   318,     0,    60,    61,    62,    63,    72,
      54,    73,     0,     0,    55,    56,     0,    57,   311,    58,
       0,     0,     0,     0,    51,     0,    52,     9,     0,    53,
       0,    74,    59,    20,     0,     0,    21,    22,     0,     0,
       0,    60,    61,    62,    63,     0,    54,     0,     0,     0,
      55,    56,     0,    57,    20,    58,     0,    21,    22,    51,
       0,    52,     9,     0,    53,     0,     0,     0,    59,    20,
       0,     0,    21,    22,   162,   163,   164,    60,    61,    62,
      63,    54,     0,     0,     0,    55,    56,     0,    57,     0,
      58,    55,    56,   167,    57,   168,    58,   169,   170,   171,
       0,     0,   197,    59,    20,     0,     0,    21,    22,   198,
       0,     0,    60,    61,    62,    63,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,     0,     6,     0,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,   315,     0,     0,     0,     0,   199,   123,
     316,     0,     0,     0,     0,     0,   268,   186,   187,   188,
     189,   190,   191,   161,   162,   163,   164,   165,   166,     0,
       0,     0,     0,   124,     0,   192,     0,     0,     0,     0,
       0,    55,    56,   167,    57,   168,    58,   169,   170,   171,
     114,   115,   116,     0,     0,   119,   120,   121,   122,   317,
       0,   172,   173,     0,     0,   269,   358,   123,   175,    61,
      62,    63,     0,   161,   162,   163,   164,   165,   166,    81,
       0,     0,     0,     0,     0,     7,     0,     8,     9,    10,
      11,    55,    56,   167,    57,   168,    58,   169,   170,   171,
       0,     0,     0,    12,    13,    14,    15,    16,    17,    18,
      19,   172,   173,     0,     0,     0,    85,     0,   175,    61,
      62,    63,     7,     0,     8,     9,    10,    11,     0,     0,
      20,     0,     0,    21,    22,     0,     0,     0,     0,     0,
      12,    13,    14,    15,    16,    17,    18,    19,    87,     0,
       0,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    12,    13,    14,    15,    16,    17,    18,    19,
      89,     0,     0,     0,     0,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    12,    13,    14,    15,    16,    17,
      18,    19,    91,     0,     0,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    12,    13,    14,    15,
      16,    17,    18,    19,    93,     0,     0,     0,     0,     0,
       7,     0,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,    20,     0,     0,    21,    22,    12,    13,
      14,    15,    16,    17,    18,    19,   226,     0,     0,     0,
       0,     0,     7,     0,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    21,    22,
      12,    13,    14,    15,    16,    17,    18,    19,   228,     0,
       0,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    12,    13,    14,    15,    16,    17,    18,    19,
     230,     0,     0,     0,     0,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    12,    13,    14,    15,    16,    17,
      18,    19,   232,     0,     0,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    12,    13,    14,    15,
      16,    17,    18,    19,   234,     0,     0,     0,     0,     0,
       7,     0,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,    20,     0,     0,    21,    22,    12,    13,
      14,    15,    16,    17,    18,    19,   236,     0,     0,     0,
       0,     0,     7,     0,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    21,    22,
      12,    13,    14,    15,    16,    17,    18,    19,   238,     0,
       0,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    12,    13,    14,    15,    16,    17,    18,    19,
     240,     0,     0,     0,     0,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    12,    13,    14,    15,    16,    17,
      18,    19,   242,     0,     0,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    12,    13,    14,    15,
      16,    17,    18,    19,   244,     0,     0,     0,     0,     0,
       7,     0,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,    20,     0,     0,    21,    22,    12,    13,
      14,    15,    16,    17,    18,    19,   246,     0,     0,     0,
       0,     0,     7,     0,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    21,    22,
      12,    13,    14,    15,    16,    17,    18,    19,   248,     0,
       0,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    12,    13,    14,    15,    16,    17,    18,    19,
     250,     0,     0,     0,     0,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    12,    13,    14,    15,    16,    17,
      18,    19,   252,     0,     0,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    12,    13,    14,    15,
      16,    17,    18,    19,   254,     0,     0,     0,     0,     0,
       7,     0,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,    20,     0,     0,    21,    22,    12,    13,
      14,    15,    16,    17,    18,    19,   338,     0,     0,     0,
       0,     0,     7,     0,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    21,    22,
      12,    13,    14,    15,    16,    17,    18,    19,   384,     0,
       0,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
      21,    22,    12,    13,    14,    15,    16,    17,    18,    19,
     386,     0,     0,     0,     0,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    22,    12,    13,    14,    15,    16,    17,
      18,    19,   388,     0,     0,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    21,    22,    12,    13,    14,    15,
      16,    17,    18,    19,   390,     0,     0,     0,     0,     0,
       7,   320,     8,     9,    10,    11,   322,    72,     0,    73,
       0,     0,    72,    20,    73,     0,    21,    22,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,    74,
     324,     0,     0,     0,    74,   326,    72,     0,    73,     0,
       0,    72,     0,    73,     0,    20,     0,     0,    21,    22,
       0,     0,    20,     0,     0,    21,    22,    20,    74,   328,
      21,    22,     0,    74,   330,    72,     0,    73,     0,     0,
      72,     0,    73,     0,     0,     7,     0,     8,     9,    10,
      11,    20,     0,     0,    21,    22,    20,    74,     0,    21,
      22,     0,    74,    12,    13,    14,    15,    16,    17,    18,
      19,   115,   116,     0,     0,   119,   120,   121,   122,     0,
      20,     0,     0,    21,    22,    20,     0,   123,    21,    22,
      20,     0,     0,    21,    22,   161,   162,   163,   164,   165,
     166,     0,     0,     0,   161,   162,   163,   164,   165,   166,
       0,     0,     0,    55,    56,   167,    57,   168,    58,   169,
     170,   171,    55,    56,   167,    57,   168,    58,   169,   170,
     171,     0,     0,     0,   173,     0,     0,     0,     0,     0,
     175,    61,    62,    63,    20,     0,     0,     0,     0,   175,
      61,    62,    63,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,   161,   162,   163,   164,   165,   166,     0,     0,
       0,     0,     0,   163,   164,     0,     0,     0,     0,     0,
      55,    56,   167,    57,   168,    58,   169,   170,   171,    55,
      56,   167,    57,   168,    58,   169,   170,   171,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,   123,    55,    56,   167,
      57,   168,    58,   169,   170,   171
  };

  const short
  parser::yycheck_[] =
  {
       7,     1,    18,    19,     0,    12,    13,    14,    15,    16,
       8,    17,    18,    19,     8,   102,    61,     8,   105,    57,
       2,     3,     4,    42,    43,    13,     7,    46,    72,    57,
      74,    42,    42,    43,    42,     1,    46,    57,     8,    17,
      18,     2,    58,     1,    70,    61,     8,    70,    30,    15,
      16,    17,    18,    19,    20,    33,    13,    57,    84,    57,
      57,    84,    57,    57,   151,    42,    57,    33,    50,    57,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,   171,    43,    44,    57,    70,    96,
      42,    57,    57,    42,    46,    57,    78,    46,    42,    57,
      57,   108,   109,   110,   111,    42,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   143,   144,   145,
     143,   144,   145,    42,   169,   170,     2,     3,     4,   155,
       1,    57,   155,    57,   160,    42,     7,   160,     9,     1,
      42,   147,   186,   187,   188,   189,   190,   191,   192,    58,
      59,     1,    42,   169,   170,   171,    42,    43,    29,    42,
      43,    57,    16,    17,    18,   171,   127,   128,   129,   130,
     131,     1,     3,     4,   135,   136,   137,   138,   139,    33,
      11,    52,    44,     1,    55,    56,    57,    42,    43,     1,
       1,    33,    42,    42,    44,    57,    46,    42,    43,   206,
     207,    44,    45,   210,   211,   212,   213,    57,   215,   216,
      42,   217,   219,   220,    44,   222,   223,   304,   224,    42,
      51,    42,    53,    54,    42,    28,    44,    57,    46,    60,
      42,    42,    44,    44,    46,    46,     1,    68,    -1,    57,
       3,    72,    -1,    74,    -1,    57,    57,    -1,    11,    42,
      43,    -1,   278,    42,    43,   278,   282,    -1,   284,   282,
     286,   284,   288,   286,   290,   288,   292,   290,    -1,   292,
     276,    11,    21,    22,    23,    24,     7,    42,     9,    44,
     306,    46,   308,   306,   310,   308,   312,   310,    51,   312,
      53,    54,    57,    -1,    -1,   301,    -1,    60,     1,    -1,
      21,    22,    23,    24,     7,    68,     9,     3,     4,     5,
       6,    51,    33,    53,    54,    -1,    47,    48,    49,    50,
      60,    -1,   153,    42,    43,    -1,    29,    -1,    68,    -1,
     161,   162,   163,   164,   165,   166,    42,    43,    -1,   346,
     347,   172,   173,    -1,   175,    -1,   353,   354,    -1,    52,
     181,    -1,    55,    56,    -1,   186,   187,   188,   189,   190,
     191,   192,   368,    -1,    -1,   372,   373,    -1,    -1,   376,
     377,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,     1,    -1,    -1,     1,
     153,    -1,    -1,    -1,    -1,     7,    -1,     9,   161,   162,
     163,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,   172,
     173,    -1,   175,   153,    -1,    -1,    -1,    29,   181,    -1,
      -1,   161,   162,   163,   164,   165,   166,    -1,    -1,    -1,
      -1,    -1,   172,   173,    -1,   175,    -1,    52,    -1,    -1,
      52,   181,    57,    55,    56,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    -1,   127,   128,   129,
     130,   131,     1,    -1,    -1,   135,   136,   137,   138,   139,
      -1,    -1,    -1,     1,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    53,    54,    -1,    -1,    57,    -1,
      -1,    60,    61,    62,    63,    53,    54,     1,    -1,    57,
      -1,    -1,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,     1,    -1,    -1,
      -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    53,
      54,    -1,    -1,    57,     1,    -1,    60,    61,    62,    63,
       7,    -1,     9,    10,    -1,    12,    -1,    -1,    52,    -1,
      -1,    55,    56,    57,    15,    16,    17,    18,    19,    20,
      -1,    -1,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
       1,    38,    33,    -1,    -1,    -1,     7,    -1,     9,    10,
      -1,    12,    -1,    -1,    51,    52,    -1,    -1,    55,    56,
      57,    -1,    -1,    60,    61,    62,    63,    -1,    29,    -1,
      -1,    -1,    33,    34,    -1,    36,     1,    38,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    -1,    12,    -1,    -1,
      51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    29,    -1,    -1,    -1,    33,    34,
      -1,    36,     1,    38,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    -1,    12,    -1,    -1,    51,    52,    -1,    -1,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      29,    -1,    -1,    -1,    33,    34,    -1,    36,     1,    38,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    -1,    12,
      -1,    -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,     1,    38,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    -1,    12,    -1,    -1,    51,    52,
      -1,    -1,    55,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
       1,    38,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      -1,    12,    -1,    -1,    51,    52,    -1,    -1,    55,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    -1,    29,    -1,
      -1,    -1,    33,    34,    -1,    36,     1,    38,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    -1,    12,    -1,    -1,
      51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    29,    -1,    -1,    -1,    33,    34,
      -1,    36,     1,    38,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    -1,    12,    -1,    -1,    51,    52,    -1,    -1,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      29,    -1,    -1,    -1,    33,    34,    -1,    36,     1,    38,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    -1,    12,
      -1,    -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,     1,    38,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    -1,    12,    -1,    -1,    51,    52,
      -1,    -1,    55,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
       1,    38,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      -1,    12,    -1,    -1,    51,    52,    -1,    -1,    55,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    -1,    29,    -1,
      -1,    -1,    33,    34,    -1,    36,     1,    38,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    -1,    12,    -1,    -1,
      51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    29,    -1,    -1,    -1,    33,    34,
      -1,    36,     1,    38,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    -1,    12,    -1,    -1,    51,    52,    -1,    -1,
      55,    56,    -1,     1,    -1,    60,    61,    62,    63,     7,
      29,     9,    -1,    -1,    33,    34,    -1,    36,     1,    38,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    -1,    12,
      -1,    29,    51,    52,    -1,    -1,    55,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    52,    38,    -1,    55,    56,     7,
      -1,     9,    10,    -1,    12,    -1,    -1,    -1,    51,    52,
      -1,    -1,    55,    56,    16,    17,    18,    60,    61,    62,
      63,    29,    -1,    -1,    -1,    33,    34,    -1,    36,    -1,
      38,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,     1,    51,    52,    -1,    -1,    55,    56,     8,
      -1,    -1,    60,    61,    62,    63,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,     1,    -1,    -1,    -1,    -1,    57,    33,
       8,    -1,    -1,    -1,    -1,    -1,     8,    15,    16,    17,
      18,    19,    20,    15,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    57,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      16,    17,    18,    -1,    -1,    21,    22,    23,    24,    57,
      -1,    53,    54,    -1,    -1,    57,     8,    33,    60,    61,
      62,    63,    -1,    15,    16,    17,    18,    19,    20,     1,
      -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,
      12,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    53,    54,    -1,    -1,    -1,     1,    -1,    60,    61,
      62,    63,     7,    -1,     9,    10,    11,    12,    -1,    -1,
      52,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    25,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,     1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    25,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,     1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    25,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,     1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    25,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    -1,    -1,    -1,    -1,
       7,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,     1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    -1,    -1,    -1,    -1,     7,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    25,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    -1,    -1,    -1,    -1,
       7,     1,     9,    10,    11,    12,     1,     7,    -1,     9,
      -1,    -1,     7,    52,     9,    -1,    55,    56,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    29,
       1,    -1,    -1,    -1,    29,     1,     7,    -1,     9,    -1,
      -1,     7,    -1,     9,    -1,    52,    -1,    -1,    55,    56,
      -1,    -1,    52,    -1,    -1,    55,    56,    52,    29,     1,
      55,    56,    -1,    29,     1,     7,    -1,     9,    -1,    -1,
       7,    -1,     9,    -1,    -1,     7,    -1,     9,    10,    11,
      12,    52,    -1,    -1,    55,    56,    52,    29,    -1,    55,
      56,    -1,    29,    25,    26,    27,    28,    29,    30,    31,
      32,    17,    18,    -1,    -1,    21,    22,    23,    24,    -1,
      52,    -1,    -1,    55,    56,    52,    -1,    33,    55,    56,
      52,    -1,    -1,    55,    56,    15,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    52,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    15,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    33,    34,    35,
      36,    37,    38,    39,    40,    41
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,    81,     1,     7,     9,    10,
      11,    12,    25,    26,    27,    28,    29,    30,    31,    32,
      52,    55,    56,    57,    82,    83,    95,    96,    98,    99,
     101,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    82,    83,    95,
     102,     7,     9,    12,    29,    33,    34,    36,    38,    51,
      60,    61,    62,    63,    82,    83,    90,    91,    94,    96,
      97,    98,     7,     9,    29,    82,    83,    96,   100,     0,
      57,     1,   101,     1,    97,     1,   101,     1,   101,     1,
     101,     1,   101,     1,   101,     1,    43,    44,    86,    87,
       1,    86,    87,     1,    86,    87,    58,    59,    47,    48,
      49,    50,    99,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    33,    57,    83,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
      57,    83,     1,    97,    97,    97,     1,    46,    84,    85,
      86,    87,    88,     7,     1,    97,     1,    86,    88,     1,
      97,    15,    16,    17,    18,    19,    20,    35,    37,    39,
      40,    41,    53,    54,    57,    60,    83,    89,    91,    92,
      93,    94,     1,   100,     1,   100,    15,    16,    17,    18,
      19,    20,    33,    57,    83,     8,    57,     1,     8,    57,
      13,    57,     1,    13,    14,    57,    42,    43,   101,    57,
      42,    43,    42,    43,    57,    42,    43,    46,    84,    42,
      43,    57,    42,    43,    46,    84,     1,   101,     1,   101,
       1,   101,     1,   101,     1,   101,     1,   101,     1,   101,
       1,   101,     1,   101,     1,   101,     1,   101,     1,   101,
       1,   101,     1,   101,     1,   101,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,     8,    57,     8,    57,
      42,    45,    87,    42,    57,    42,    46,    84,    97,    42,
      57,     1,    97,     1,    97,     1,    97,     1,    97,     1,
      97,     1,    97,     1,    86,    88,     1,    86,    88,     1,
      42,    46,    84,    86,    87,     1,    97,     1,    97,     1,
      97,     1,    97,     8,    57,     1,     8,    57,     1,   100,
       1,   100,     1,   100,     1,   100,     1,   100,     1,   100,
       1,   100,     8,    57,    13,    57,   101,   101,     1,   101,
     101,   101,   101,   101,   101,    87,    42,    43,   101,   101,
     101,   101,    87,    42,    43,    42,    87,    42,     8,    42,
      57,    42,    57,    42,    87,    42,    57,    42,    46,    84,
       8,    57,    42,    43,   101,   101,    42,    43,   101,   101,
      42,    42,    87,    42,     1,   101,     1,   101,     1,   101,
       1,   101,    42
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    82,    83,
      84,    84,    85,    85,    86,    86,    87,    88,    88,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    94,    94,
      95,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    98,    98,
      98,    99,    99,    99,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     2,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     2,     3,     2,     1,     2,
       1,     2,     0,     1,     0,     1,     1,     4,     3,     3,
       2,     2,     5,     4,     4,     3,     2,     3,     3,     3,
       1,     1,     1,     1,     2,     3,     3,     1,     1,     2,
       3,     3,     2,     3,     3,     2,     3,     3,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     2,     2,
       3,     3,     1,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     4,     3,     4,     3,     3,     4,     3,
       1,     1,     3,     4,     3,     3,     4,     3,     1,     1,
       3,     4,     3,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     4,
       6,     6,     5,     5,     6,     6,     3,     4,     4,     2,
       2,     6,     6,     5,     5,     4,     4,     6,     6,     3,
       4,     4,     2,     2,     2,     2,     4,     4,     4,     3,
       4,     4,     3,     2,     2,     1,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     2,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     3,     3,
       3,     3,     1,     1
  };


#if TLYYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"LTL start marker\"",
  "\"LBT start marker\"", "\"SERE start marker\"",
  "\"BOOLEAN start marker\"", "\"opening parenthesis\"",
  "\"closing parenthesis\"", "\"(...) block\"", "\"{...} block\"",
  "\"{...}! block\"", "\"opening brace\"", "\"closing brace\"",
  "\"closing brace-bang\"", "\"or operator\"", "\"xor operator\"",
  "\"and operator\"", "\"short and operator\"", "\"implication operator\"",
  "\"equivalent operator\"", "\"until operator\"", "\"release operator\"",
  "\"weak until operator\"", "\"strong release operator\"",
  "\"sometimes operator\"", "\"always operator\"", "\"next operator\"",
  "\"strong next operator\"", "\"not operator\"", "\"X[.] operator\"",
  "\"F[.] operator\"", "\"G[.] operator\"", "\"star operator\"",
  "\"bracket star operator\"", "\"bracket fusion-star operator\"",
  "\"plus operator\"", "\"fusion-plus operator\"",
  "\"opening bracket for star operator\"",
  "\"opening bracket for fusion-star operator\"",
  "\"opening bracket for equal operator\"",
  "\"opening bracket for goto operator\"", "\"closing bracket\"",
  "\"closing !]\"", "\"number for square bracket operator\"",
  "\"unbounded mark\"", "\"separator for square bracket operator\"",
  "\"universal concat operator\"", "\"existential concat operator\"",
  "\"universal non-overlapping concat operator\"",
  "\"existential non-overlapping concat operator\"", "\"first_match\"",
  "\"atomic proposition\"", "\"concat operator\"", "\"fusion operator\"",
  "\"constant true\"", "\"constant false\"", "\"end of formula\"",
  "\"negative suffix\"", "\"positive suffix\"", "\"SVA delay operator\"",
  "\"opening bracket for SVA delay operator\"", "\"##[+] operator\"",
  "\"##[*] operator\"", "'!'", "'&'", "'|'", "'^'", "'i'", "'e'", "'X'",
  "'F'", "'G'", "'U'", "'V'", "'R'", "'W'", "'M'", "'t'", "'f'", "$accept",
  "result", "emptyinput", "enderror", "OP_SQBKT_SEP_unbounded",
  "OP_SQBKT_SEP_opt", "error_opt", "sqbkt_num", "sqbracketargs",
  "gotoargs", "kleen_star", "starargs", "fstarargs", "equalargs",
  "delayargs", "atomprop", "booleanatom", "sere", "bracedsere",
  "parenthesedsubformula", "boolformula", "subformula", "lbtformula", YY_NULLPTR
  };
#endif


#if TLYYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   294,   294,   299,   304,   309,   311,   316,   321,   326,
     328,   333,   338,   343,   345,   350,   355,   360,   363,   369,
     375,   375,   376,   377,   378,   379,   381,   399,   401,   403,
     405,   407,   411,   413,   415,   417,   419,   421,   423,   426,
     431,   431,   433,   435,   437,   439,   442,   446,   448,   450,
     452,   456,   461,   463,   466,   471,   473,   476,   480,   482,
     485,   493,   494,   495,   499,   501,   504,   505,   517,   518,
     527,   529,   535,   539,   545,   547,   550,   552,   555,   557,
     559,   561,   563,   565,   567,   569,   571,   574,   576,   586,
     588,   598,   600,   609,   618,   627,   645,   663,   677,   679,
     692,   694,   708,   710,   713,   715,   719,   724,   729,   734,
     740,   750,   758,   760,   764,   769,   773,   778,   786,   787,
     796,   798,   802,   807,   812,   817,   823,   825,   827,   829,
     831,   833,   835,   837,   839,   841,   843,   845,   847,   849,
     851,   853,   856,   857,   858,   860,   862,   864,   866,   868,
     870,   872,   874,   876,   878,   880,   882,   884,   886,   888,
     890,   892,   894,   896,   898,   900,   902,   904,   906,   911,
     917,   920,   924,   928,   932,   935,   938,   941,   945,   949,
     951,   953,   956,   960,   964,   968,   973,   980,   983,   986,
     989,   993,   997,   999,  1001,  1003,  1005,  1007,  1009,  1012,
    1014,  1018,  1021,  1024,  1026,  1028,  1030,  1032,  1034,  1037,
    1039,  1043,  1048,  1052,  1057,  1061,  1064,  1075,  1076,  1078,
    1080,  1082,  1084,  1086,  1088,  1090,  1092,  1094,  1096,  1098,
    1100,  1102,  1104,  1106
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // TLYYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,     2,     2,     2,    65,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      71,    72,     2,     2,     2,     2,     2,    77,     2,     2,
       2,     2,    75,     2,     2,    73,    74,    76,    70,     2,
       2,     2,     2,     2,    67,     2,     2,     2,     2,     2,
       2,    69,    79,     2,     2,    68,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    78,     2,     2,     2,
       2,     2,     2,     2,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
    };
    // Last valid token kind.
    const int code_max = 318;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // tlyy
#line 3822 "parsetl.cc"

#line 1110 "parsetl.yy"


void
tlyy::parser::error(const location_type& location, const std::string& message)
{
  error_list.emplace_back(location, message);
}

namespace spot
{
  parsed_formula
  parse_infix_psl(const std::string& ltl_string,
		  environment& env,
		  bool debug, bool lenient)
  {
    parsed_formula result(ltl_string);
    flex_set_buffer(ltl_string,
		    tlyy::parser::token::START_LTL,
		    lenient);
    tlyy::parser parser(result.errors, env, result.f);
    parser.set_debug_level(debug);
    parser.parse();
    flex_unset_buffer();
    return result;
  }

  parsed_formula
  parse_infix_boolean(const std::string& ltl_string,
		      environment& env,
		      bool debug, bool lenient)
  {
    parsed_formula result(ltl_string);
    flex_set_buffer(ltl_string,
		    tlyy::parser::token::START_BOOL,
		    lenient);
    tlyy::parser parser(result.errors, env, result.f);
    parser.set_debug_level(debug);
    parser.parse();
    flex_unset_buffer();
    return result;
  }

  parsed_formula
  parse_prefix_ltl(const std::string& ltl_string,
		   environment& env,
		   bool debug)
  {
    parsed_formula result(ltl_string);
    flex_set_buffer(ltl_string,
		    tlyy::parser::token::START_LBT,
		    false);
    tlyy::parser parser(result.errors, env, result.f);
    parser.set_debug_level(debug);
    parser.parse();
    flex_unset_buffer();
    return result;
  }

  parsed_formula
  parse_infix_sere(const std::string& sere_string,
		   environment& env,
		   bool debug,
		   bool lenient)
  {
    parsed_formula result(sere_string);
    flex_set_buffer(sere_string,
		    tlyy::parser::token::START_SERE,
		    lenient);
    tlyy::parser parser(result.errors, env, result.f);
    parser.set_debug_level(debug);
    parser.parse();
    flex_unset_buffer();
    return result;
  }

  formula
  parse_formula(const std::string& ltl_string, environment& env)
  {
    parsed_formula pf = parse_infix_psl(ltl_string, env);
    std::ostringstream s;
    if (pf.format_errors(s))
      {
	parsed_formula pg = parse_prefix_ltl(ltl_string, env);
	if (pg.errors.empty())
	  return pg.f;
	else
	  throw parse_error(s.str());
      }
    return pf.f;
  }
}

// Local Variables:
// mode: c++
// End:
