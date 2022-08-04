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
#define yylex   hoayylex



#include "parseaut.hh"


// Unqualified %code blocks.
#line 217 "parseaut.yy"

#include <sstream>

  /* parseaut.hh and parsedecl.hh include each other recursively.
   We must ensure that YYSTYPE is declared (by the above %union)
   before parsedecl.hh uses it. */
#include <spot/parseaut/parsedecl.hh>

  static void fill_guards(result_& res);

#line 59 "parseaut.cc"


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
#if HOAYYDEBUG

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

#else // !HOAYYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !HOAYYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace hoayy {
#line 151 "parseaut.cc"

  /// Build a parser object.
  parser::parser (void* scanner_yyarg, result_& res_yyarg, spot::location initial_loc_yyarg)
#if HOAYYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      res (res_yyarg),
      initial_loc (initial_loc_yyarg)
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
      case symbol_kind::S_IDENTIFIER: // "identifier"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 359 "parseaut.cc"
        break;

      case symbol_kind::S_HEADERNAME: // "header name"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 365 "parseaut.cc"
        break;

      case symbol_kind::S_ANAME: // "alias name"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 371 "parseaut.cc"
        break;

      case symbol_kind::S_STRING: // "string"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 377 "parseaut.cc"
        break;

      case symbol_kind::S_24_: // '['
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 383 "parseaut.cc"
        break;

      case symbol_kind::S_LINEDIRECTIVE: // "#line"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 389 "parseaut.cc"
        break;

      case symbol_kind::S_BDD: // BDD
#line 309 "parseaut.yy"
                    { bdd_delref((yysym.value.b)); }
#line 395 "parseaut.cc"
        break;

      case symbol_kind::S_FORMULA: // "boolean formula"
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 401 "parseaut.cc"
        break;

      case symbol_kind::S_string_opt: // string_opt
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 407 "parseaut.cc"
        break;

      case symbol_kind::S_96_state_conj_2: // state-conj-2
#line 312 "parseaut.yy"
                    { delete (yysym.value.states); }
#line 413 "parseaut.cc"
        break;

      case symbol_kind::S_97_init_state_conj_2: // init-state-conj-2
#line 312 "parseaut.yy"
                    { delete (yysym.value.states); }
#line 419 "parseaut.cc"
        break;

      case symbol_kind::S_98_label_expr: // label-expr
#line 309 "parseaut.yy"
                    { bdd_delref((yysym.value.b)); }
#line 425 "parseaut.cc"
        break;

      case symbol_kind::S_100_acceptance_cond: // acceptance-cond
#line 311 "parseaut.yy"
                    { delete (yysym.value.code); }
#line 431 "parseaut.cc"
        break;

      case symbol_kind::S_118_state_conj_checked: // state-conj-checked
#line 312 "parseaut.yy"
                    { delete (yysym.value.states); }
#line 437 "parseaut.cc"
        break;

      case symbol_kind::S_135_nc_one_ident: // nc-one-ident
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 443 "parseaut.cc"
        break;

      case symbol_kind::S_136_nc_ident_list: // nc-ident-list
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 449 "parseaut.cc"
        break;

      case symbol_kind::S_137_nc_transition_block: // nc-transition-block
#line 327 "parseaut.yy"
                    {
  for (auto i = (yysym.value.list)->begin(); i != (yysym.value.list)->end(); ++i)
  {
    bdd_delref(i->first);
    delete i->second;
  }
  delete (yysym.value.list);
  }
#line 462 "parseaut.cc"
        break;

      case symbol_kind::S_139_nc_transitions: // nc-transitions
#line 327 "parseaut.yy"
                    {
  for (auto i = (yysym.value.list)->begin(); i != (yysym.value.list)->end(); ++i)
  {
    bdd_delref(i->first);
    delete i->second;
  }
  delete (yysym.value.list);
  }
#line 475 "parseaut.cc"
        break;

      case symbol_kind::S_140_nc_formula_or_ident: // nc-formula-or-ident
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 481 "parseaut.cc"
        break;

      case symbol_kind::S_141_nc_formula: // nc-formula
#line 309 "parseaut.yy"
                    { bdd_delref((yysym.value.b)); }
#line 487 "parseaut.cc"
        break;

      case symbol_kind::S_142_nc_opt_dest: // nc-opt-dest
#line 308 "parseaut.yy"
                    { delete (yysym.value.str); }
#line 493 "parseaut.cc"
        break;

      case symbol_kind::S_143_nc_src_dest: // nc-src-dest
#line 310 "parseaut.yy"
                    { bdd_delref((yysym.value.p)->first); delete (yysym.value.p)->second; delete (yysym.value.p); }
#line 499 "parseaut.cc"
        break;

      case symbol_kind::S_144_nc_transition: // nc-transition
#line 310 "parseaut.yy"
                    { bdd_delref((yysym.value.p)->first); delete (yysym.value.p)->second; delete (yysym.value.p); }
#line 505 "parseaut.cc"
        break;

      default:
        break;
    }
  }

#if HOAYYDEBUG
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
      case symbol_kind::S_IDENTIFIER: // "identifier"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 537 "parseaut.cc"
        break;

      case symbol_kind::S_HEADERNAME: // "header name"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 547 "parseaut.cc"
        break;

      case symbol_kind::S_ANAME: // "alias name"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 557 "parseaut.cc"
        break;

      case symbol_kind::S_STRING: // "string"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 567 "parseaut.cc"
        break;

      case symbol_kind::S_INT: // "integer"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 573 "parseaut.cc"
        break;

      case symbol_kind::S_24_: // '['
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 583 "parseaut.cc"
        break;

      case symbol_kind::S_LINEDIRECTIVE: // "#line"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 593 "parseaut.cc"
        break;

      case symbol_kind::S_FORMULA: // "boolean formula"
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 603 "parseaut.cc"
        break;

      case symbol_kind::S_LBTT: // "LBTT header"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 609 "parseaut.cc"
        break;

      case symbol_kind::S_INT_S: // "state acceptance"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 615 "parseaut.cc"
        break;

      case symbol_kind::S_LBTT_EMPTY: // "acceptance sets for empty automaton"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 621 "parseaut.cc"
        break;

      case symbol_kind::S_ACC: // "acceptance set"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 627 "parseaut.cc"
        break;

      case symbol_kind::S_STATE_NUM: // "state number"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 633 "parseaut.cc"
        break;

      case symbol_kind::S_DEST_NUM: // "destination number"
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 639 "parseaut.cc"
        break;

      case symbol_kind::S_string_opt: // string_opt
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 649 "parseaut.cc"
        break;

      case symbol_kind::S_96_state_conj_2: // state-conj-2
#line 313 "parseaut.yy"
                 {
  auto& os = debug_stream();
  os << '{';
  bool notfirst = false;
  for (auto i: *(yysym.value.states))
  {
    if (notfirst)
      os << ", ";
    else
      notfirst = true;
    os << i;
  }
  os << '}';
}
#line 668 "parseaut.cc"
        break;

      case symbol_kind::S_97_init_state_conj_2: // init-state-conj-2
#line 313 "parseaut.yy"
                 {
  auto& os = debug_stream();
  os << '{';
  bool notfirst = false;
  for (auto i: *(yysym.value.states))
  {
    if (notfirst)
      os << ", ";
    else
      notfirst = true;
    os << i;
  }
  os << '}';
}
#line 687 "parseaut.cc"
        break;

      case symbol_kind::S_99_acc_set: // acc-set
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 693 "parseaut.cc"
        break;

      case symbol_kind::S_102_state_num: // state-num
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 699 "parseaut.cc"
        break;

      case symbol_kind::S_103_checked_state_num: // checked-state-num
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 705 "parseaut.cc"
        break;

      case symbol_kind::S_118_state_conj_checked: // state-conj-checked
#line 313 "parseaut.yy"
                 {
  auto& os = debug_stream();
  os << '{';
  bool notfirst = false;
  for (auto i: *(yysym.value.states))
  {
    if (notfirst)
      os << ", ";
    else
      notfirst = true;
    os << i;
  }
  os << '}';
}
#line 724 "parseaut.cc"
        break;

      case symbol_kind::S_sign: // sign
#line 340 "parseaut.yy"
                 { debug_stream() << (yysym.value.num); }
#line 730 "parseaut.cc"
        break;

      case symbol_kind::S_135_nc_one_ident: // nc-one-ident
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 740 "parseaut.cc"
        break;

      case symbol_kind::S_136_nc_ident_list: // nc-ident-list
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 750 "parseaut.cc"
        break;

      case symbol_kind::S_140_nc_formula_or_ident: // nc-formula-or-ident
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 760 "parseaut.cc"
        break;

      case symbol_kind::S_142_nc_opt_dest: // nc-opt-dest
#line 335 "parseaut.yy"
                 {
    if ((yysym.value.str))
      debug_stream() << *(yysym.value.str);
    else
      debug_stream() << "\"\""; }
#line 770 "parseaut.cc"
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

#if HOAYYDEBUG
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
#endif // HOAYYDEBUG

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


    // User initialization code.
#line 202 "parseaut.yy"
{ yyla.location = res.h->loc = initial_loc; }

#line 892 "parseaut.cc"


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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, scanner, PARSE_ERROR_LIST));
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
  case 2: // aut: aut-1
#line 343 "parseaut.yy"
               { res.h->loc = yylhs.location; YYACCEPT; }
#line 1030 "parseaut.cc"
    break;

  case 3: // $@1: %empty
#line 347 "parseaut.yy"
                   { res.h->filename = *(yystack_[0].value.str); }
#line 1036 "parseaut.cc"
    break;

  case 5: // aut: "end of file"
#line 348 "parseaut.yy"
               { YYABORT; }
#line 1042 "parseaut.cc"
    break;

  case 6: // aut: error "end of file"
#line 349 "parseaut.yy"
                     { YYABORT; }
#line 1048 "parseaut.cc"
    break;

  case 7: // aut: error aut-1
#line 351 "parseaut.yy"
     {
       error(yystack_[1].location, "leading garbage was ignored");
       res.h->loc = yystack_[0].location;
       YYACCEPT;
     }
#line 1058 "parseaut.cc"
    break;

  case 8: // aut-1: hoa
#line 357 "parseaut.yy"
             { res.h->type = spot::parsed_aut_type::HOA; }
#line 1064 "parseaut.cc"
    break;

  case 9: // aut-1: never
#line 358 "parseaut.yy"
             { res.h->type = spot::parsed_aut_type::NeverClaim; }
#line 1070 "parseaut.cc"
    break;

  case 10: // aut-1: lbtt
#line 359 "parseaut.yy"
             { res.h->type = spot::parsed_aut_type::LBTT; }
#line 1076 "parseaut.cc"
    break;

  case 14: // string_opt: %empty
#line 369 "parseaut.yy"
                   { (yylhs.value.str) = nullptr; }
#line 1082 "parseaut.cc"
    break;

  case 15: // string_opt: "string"
#line 370 "parseaut.yy"
                   { (yylhs.value.str) = (yystack_[0].value.str); }
#line 1088 "parseaut.cc"
    break;

  case 18: // header: format-version header-items
#line 374 "parseaut.yy"
        {
          bool v1plus = strverscmp("v1", res.format_version.c_str()) < 0;
	  // Preallocate the states if we know their number.
	  if (res.states >= 0)
	    {
	      unsigned states = res.states;
	      for (auto& p : res.start)
                for (unsigned s: p.second)
                  if ((unsigned) res.states <= s)
                    {
                      error(p.first, "initial state number is larger "
                            "than state count...");
                      error(res.states_loc, "... declared here.");
                      states = std::max(states, s + 1);
                    }
	      if (res.opts.want_kripke)
		res.h->ks->new_states(states, bddfalse);
	      else
		res.h->aut->new_states(states);
	      res.info_states.resize(states);
	    }
	  if (res.accset < 0)
	    {
	      error(yylhs.location, "missing 'Acceptance:' header");
	      res.ignore_acc = true;
	    }
          if (res.unknown_ap_max >= 0 && !res.ignore_more_ap)
            {
              error(res.unknown_ap_max_location,
                    "atomic proposition used in Alias without AP declaration");
              for (auto& p: res.alias)
                p.second = bddtrue;
            }
	  // Process properties.
	  {
	    auto explicit_labels = res.prop_is_true("explicit-labels");
	    auto implicit_labels = res.prop_is_true("implicit-labels");

	    if (implicit_labels)
	      {
		if (res.opts.want_kripke)
		  error(implicit_labels.loc,
			"Kripke structure may not use implicit labels");

		if (explicit_labels)
		  {
		    error(implicit_labels.loc,
			  "'properties: implicit-labels' is incompatible "
			  "with...");
		    error(explicit_labels.loc,
			  "... 'properties: explicit-labels'.");
		  }
		else
		  {
		    res.label_style = Implicit_Labels;
		  }
	      }

	    auto trans_labels = res.prop_is_true("trans-labels");
	    auto state_labels = res.prop_is_true("state-labels");

	    if (trans_labels)
	      {
		if (res.opts.want_kripke)
		  error(trans_labels.loc,
			"Kripke structures may not use transition labels");

		if (state_labels)
		  {
		    error(trans_labels.loc,
			  "'properties: trans-labels' is incompatible with...");
		    error(state_labels.loc,
			  "... 'properties: state-labels'.");
		  }
		else
		  {
		    if (res.label_style != Implicit_Labels)
		      res.label_style = Trans_Labels;
		  }
	      }
	    else if (state_labels)
	      {
		if (res.label_style != Implicit_Labels)
		  {
		    res.label_style = State_Labels;
		  }
		else
		  {
		    error(state_labels.loc,
			  "'properties: state-labels' is incompatible with...");
		    error(implicit_labels.loc,
			  "... 'properties: implicit-labels'.");
		  }
	      }

	    if (res.opts.want_kripke && res.label_style != State_Labels)
	      error(yylhs.location,
		    "Kripke structures should use 'properties: state-labels'");

	    auto state_acc = res.prop_is_true("state-acc");
	    auto trans_acc = res.prop_is_true("trans-acc");
	    if (trans_acc)
	      {
		if (state_acc)
		  {
		    error(trans_acc.loc,
			  "'properties: trans-acc' is incompatible with...");
		    error(state_acc.loc,
			  "... 'properties: state-acc'.");
		  }
		else
		  {
		    res.acc_style = Trans_Acc;
		  }
	      }
	    else if (state_acc)
	      {
		res.acc_style = State_Acc;
	      }

            if (auto univ_branch = res.prop_is_true("univ-branch"))
              if (res.opts.want_kripke)
                error(univ_branch.loc,
                    "Kripke structures may not use 'properties: univ-branch'");
          }
	  {
	    unsigned ss = res.start.size();
	    auto det = res.prop_is_true("deterministic");
	    auto no_exist = res.prop_is_false("exist-branch");
	    if (ss > 1)
	      {
		if (det)
		  {
		    error(det.loc,
			  "deterministic automata should have at most "
			  "one initial state");
                    res.universal = spot::trival::maybe();
		  }
                else if (no_exist)
                  {
		    error(no_exist.loc,
			  "universal automata should have at most "
			  "one initial state");
                    res.universal = spot::trival::maybe();
                  }
	      }
	    else
	      {
		// Assume the automaton is deterministic until proven
		// wrong, or unless we are building a Kripke structure.
                if (!res.opts.want_kripke)
                  {
                    res.universal = true;
                    res.existential = true;
                  }
	      }
            for (auto& ss: res.start)
              {
                if (ss.second.size() > 1)
                  {
                    if (auto no_univ = res.prop_is_false("univ-branch"))
                      {
                        error(ss.first,
                              "conjunct initial state despite...");
                        error(no_univ.loc, "... property: !univ-branch");
                      }
                    else if (v1plus)
                      if (auto det = res.prop_is_true("deterministic"))
                        {
                          error(ss.first,
                                "conjunct initial state despite...");
                          error(det.loc, "... property: deterministic");
                        }
                    res.existential = false;
                  }
              }
	    auto complete = res.prop_is_true("complete");
	    if (ss < 1)
	      {
		if (complete)
		  {
		    error(complete.loc,
			  "complete automata should have at least "
			  "one initial state");
		  }
		res.complete = false;
	      }
	    else
	      {
		// Assume the automaton is complete until proven
		// wrong.
                if (!res.opts.want_kripke)
                  res.complete = true;
	      }
	    // if ap_count == 0, then a Kripke structure could be
	    // declared complete, although that probably doesn't
	    // matter.
	    if (res.opts.want_kripke && complete && res.ap_count > 0)
	      error(complete.loc,
		    "Kripke structure may not be complete");
	  }
	  if (res.opts.trust_hoa)
	    {
	      auto& a = res.aut_or_ks;
	      auto& p = res.props;
	      auto e = p.end();
	      auto si = p.find("stutter-invariant");
	      if (si != e)
		{
		  a->prop_stutter_invariant(si->second.val);
		  auto i = p.find("stutter-sensitive");
		  if (i != e && si->second.val == i->second.val)
		    error(i->second.loc,
			  "automaton cannot be both stutter-invariant"
			  "and stutter-sensitive");
		}
	      else
		{
		  auto ss = p.find("stutter-sensitive");
		  if (ss != e)
		    a->prop_stutter_invariant(!ss->second.val);
		}
	      auto iw = p.find("inherently-weak");
	      auto vw = p.find("very-weak");
	      auto w = p.find("weak");
	      auto t = p.find("terminal");
              if (vw != e)
                {
                  a->prop_very_weak(vw->second.val);
                  if (w != e && !w->second.val && vw->second.val)
                    {
		      error(w->second.loc,
                            "'properties: !weak' contradicts...");
		      error(vw->second.loc,
			    "... 'properties: very-weak' given here");
                    }
                  if (iw != e && !iw->second.val && vw->second.val)
                    {
		      error(iw->second.loc,
                            "'properties: !inherently-weak' contradicts...");
		      error(vw->second.loc,
			    "... 'properties: very-weak' given here");
                    }
                }
	      if (iw != e)
		{
		  a->prop_inherently_weak(iw->second.val);
		  if (w != e && !iw->second.val && w->second.val)
		    {
		      error(w->second.loc, "'properties: weak' contradicts...");
		      error(iw->second.loc,
			    "... 'properties: !inherently-weak' given here");
		    }
		  if (t != e && !iw->second.val && t->second.val)
		    {
		      error(t->second.loc,
			    "'properties: terminal' contradicts...");
		      error(iw->second.loc,
			    "... 'properties: !inherently-weak' given here");
		    }
		}
	      if (w != e)
		{
		  a->prop_weak(w->second.val);
		  if (t != e && !w->second.val && t->second.val)
		    {
		      error(t->second.loc,
			    "'properties: terminal' contradicts...");
		      error(w->second.loc,
			    "... 'properties: !weak' given here");
		    }
		}
	      if (t != e)
		a->prop_terminal(t->second.val);
	      auto u = p.find("unambiguous");
	      if (u != e)
		{
		  a->prop_unambiguous(u->second.val);
		  auto d = p.find("deterministic");
		  if (d != e && !u->second.val && d->second.val)
		    {
		      error(d->second.loc,
			    "'properties: deterministic' contradicts...");
		      error(u->second.loc,
			    "... 'properties: !unambiguous' given here");
		    }
		}
	      auto sd = p.find("semi-deterministic");
	      if (sd != e)
		{
		  a->prop_semi_deterministic(sd->second.val);
		  auto d = p.find("deterministic");
		  if (d != e && !sd->second.val && d->second.val)
		    {
		      error(d->second.loc,
			    "'properties: deterministic' contradicts...");
		      error(sd->second.loc,
			    "... 'properties: !semi-deterministic' given here");
		    }
		}
	    }
	}
#line 1395 "parseaut.cc"
    break;

  case 19: // version: "identifier"
#line 678 "parseaut.yy"
         {
	   res.format_version = *(yystack_[0].value.str);
	   res.format_version_loc = yystack_[0].location;
	   delete (yystack_[0].value.str);
	 }
#line 1405 "parseaut.cc"
    break;

  case 20: // $@2: %empty
#line 684 "parseaut.yy"
                       { res.h->loc = yystack_[0].location; }
#line 1411 "parseaut.cc"
    break;

  case 22: // $@3: %empty
#line 687 "parseaut.yy"
     {
       if (res.ignore_more_ap)
	 {
	   error(yystack_[1].location, "ignoring this redeclaration of APs...");
	   error(res.ap_loc, "... previously declared here.");
	 }
       else
	 {
	   res.ap_count = (yystack_[0].value.num);
	   res.ap.reserve((yystack_[0].value.num));
	 }
     }
#line 1428 "parseaut.cc"
    break;

  case 23: // aps: "AP:" "integer" $@3 ap-names
#line 700 "parseaut.yy"
     {
       if (!res.ignore_more_ap)
	 {
	   res.ap_loc = yystack_[3].location + yystack_[2].location;
	   if ((int) res.ap.size() != res.ap_count)
	     {
	       std::ostringstream out;
	       out << "found " << res.ap.size()
		   << " atomic propositions instead of the "
		   << res.ap_count << " announced";
	       error(yylhs.location, out.str());
	     }
	   res.ignore_more_ap = true;
           // If we have seen Alias: before AP: we have some variable
           // renaming to perform.
           if (res.unknown_ap_max >= 0)
             {
               int apsize = res.ap.size();
               if (apsize <= res.unknown_ap_max)
                 {
                   error(res.unknown_ap_max_location,
                         "AP number is larger than the number of APs...");
                   error(yystack_[3].location, "... declared here");
                 }
               bddPair* pair = bdd_newpair();
               int max = std::min(res.unknown_ap_max, apsize - 1);
               for (int i = 0; i <= max; ++i)
                 if (i != res.ap[i])
                   bdd_setbddpair(pair, i, res.ap[i]);
               bdd extra = bddtrue;
               for (int i = apsize; i <= res.unknown_ap_max; ++i)
                 extra &= bdd_ithvar(i);
               for (auto& p: res.alias)
                 p.second = bdd_restrict(bdd_replace(p.second, pair), extra);
               bdd_freepair(pair);
             }
	 }
     }
#line 1471 "parseaut.cc"
    break;

  case 26: // header-item: "States:" "integer"
#line 742 "parseaut.yy"
           {
	     if (res.states >= 0)
	       {
		 error(yylhs.location, "redefinition of the number of states...");
		 error(res.states_loc, "... previously defined here.");
	       }
	     else
	       {
		 res.states_loc = yylhs.location;
	       }
	     if (((int) (yystack_[0].value.num)) < 0)
	       {
		 error(yylhs.location, "too many states for this implementation");
		 YYABORT;
	       }
	     res.states = std::max(res.states, (int) (yystack_[0].value.num));
	   }
#line 1493 "parseaut.cc"
    break;

  case 27: // header-item: "Start:" init-state-conj-2
#line 760 "parseaut.yy"
             {
               res.start.emplace_back(yylhs.location, *(yystack_[0].value.states));
               delete (yystack_[0].value.states);
	     }
#line 1502 "parseaut.cc"
    break;

  case 28: // header-item: "Start:" state-num
#line 765 "parseaut.yy"
             {
	       res.start.emplace_back(yylhs.location, std::vector<unsigned>{(yystack_[0].value.num)});
	     }
#line 1510 "parseaut.cc"
    break;

  case 30: // $@4: %empty
#line 769 "parseaut.yy"
                            { res.in_alias=true; }
#line 1516 "parseaut.cc"
    break;

  case 31: // header-item: "Alias:" "alias name" $@4 label-expr
#line 770 "parseaut.yy"
             {
               res.in_alias = false;
	       if (!res.alias.emplace(*(yystack_[2].value.str), bdd_from_int((yystack_[0].value.b))).second)
		 {
		   std::ostringstream o;
		   o << "ignoring redefinition of alias @" << *(yystack_[2].value.str);
		   error(yylhs.location, o.str());
		 }
	       delete (yystack_[2].value.str);
	       bdd_delref((yystack_[0].value.b));
	     }
#line 1532 "parseaut.cc"
    break;

  case 32: // $@5: %empty
#line 782 "parseaut.yy"
              {
		if (res.ignore_more_acc)
		  {
		    error(yystack_[1].location + yystack_[0].location, "ignoring this redefinition of the "
			  "acceptance condition...");
		    error(res.accset_loc, "... previously defined here.");
		  }
		else if ((yystack_[0].value.num) > SPOT_MAX_ACCSETS)
		  {
		    error(yystack_[1].location + yystack_[0].location,
			  "this implementation cannot support such a large "
			  "number of acceptance sets");
		    YYABORT;
		  }
		else
		  {
		    res.aut_or_ks->acc().add_sets((yystack_[0].value.num));
		    res.accset = (yystack_[0].value.num);
		    res.accset_loc = yystack_[1].location + yystack_[0].location;
		  }
	     }
#line 1558 "parseaut.cc"
    break;

  case 33: // header-item: "Acceptance:" "integer" $@5 acceptance-cond
#line 804 "parseaut.yy"
             {
	       res.ignore_more_acc = true;
	       // Not setting the acceptance in case of error will
	       // force it to be true.
	       if (res.opts.want_kripke && (!(yystack_[0].value.code)->is_t() || (yystack_[2].value.num) > 0))
		 error(yystack_[2].location + yystack_[0].location,
		       "the acceptance for Kripke structure must be '0 t'");
	       else
		 res.aut_or_ks->set_acceptance((yystack_[2].value.num), *(yystack_[0].value.code));
	       delete (yystack_[0].value.code);
	     }
#line 1574 "parseaut.cc"
    break;

  case 34: // header-item: "acc-name:" "identifier" acc-spec
#line 816 "parseaut.yy"
             {
	       delete (yystack_[1].value.str);
	     }
#line 1582 "parseaut.cc"
    break;

  case 35: // header-item: "tool:" "string" string_opt
#line 820 "parseaut.yy"
             {
	       delete (yystack_[1].value.str);
	       delete (yystack_[0].value.str);
	     }
#line 1591 "parseaut.cc"
    break;

  case 36: // header-item: "name:" "string"
#line 825 "parseaut.yy"
             {
	       res.aut_or_ks->set_named_prop("automaton-name", (yystack_[0].value.str));
	     }
#line 1599 "parseaut.cc"
    break;

  case 38: // $@6: %empty
#line 830 "parseaut.yy"
             { res.highlight_edges = new std::map<unsigned, unsigned>; }
#line 1605 "parseaut.cc"
    break;

  case 40: // $@7: %empty
#line 833 "parseaut.yy"
             { res.highlight_states = new std::map<unsigned, unsigned>; }
#line 1611 "parseaut.cc"
    break;

  case 42: // $@8: %empty
#line 836 "parseaut.yy"
             { auto p = new std::vector<bool>;
               if (res.states >= 0)
                 p->reserve(res.states);
               res.state_player = p;
             }
#line 1621 "parseaut.cc"
    break;

  case 43: // header-item: "spot.state-player:" $@8 state-player
#line 841 "parseaut.yy"
             {
               res.state_player_loc = yylhs.location;
             }
#line 1629 "parseaut.cc"
    break;

  case 44: // header-item: "header name" header-spec
#line 845 "parseaut.yy"
             {
	       char c = (*(yystack_[1].value.str))[0];
	       if (c >= 'A' && c <= 'Z')
		 error(yylhs.location, "ignoring unsupported header \"" + *(yystack_[1].value.str) + ":\"\n\t"
		       "(but the capital indicates information that should not"
		       " be ignored)");
	       delete (yystack_[1].value.str);
	     }
#line 1642 "parseaut.cc"
    break;

  case 48: // ap-name: "string"
#line 858 "parseaut.yy"
         {
	   if (!res.ignore_more_ap)
	     {
	       auto f = res.env->require(*(yystack_[0].value.str));
	       int b = 0;
	       if (f == nullptr)
		 {
		   std::ostringstream out;
		   out << "unknown atomic proposition \"" << *(yystack_[0].value.str) << "\"";
		   error(yystack_[0].location, out.str());
		   b = res.aut_or_ks->register_ap("$unknown$");
		 }
	       else
		 {
		   b = res.aut_or_ks->register_ap(f);
		   if (!res.ap_set.emplace(b).second)
		     {
		       std::ostringstream out;
		       out << "duplicate atomic proposition \"" << *(yystack_[0].value.str) << "\"";
		       error(yystack_[0].location, out.str());
		     }
		 }
	       res.ap.push_back(b);
	     }
	   delete (yystack_[0].value.str);
	 }
#line 1673 "parseaut.cc"
    break;

  case 52: // acc-spec: acc-spec "identifier"
#line 889 "parseaut.yy"
            {
	      delete (yystack_[0].value.str);
	    }
#line 1681 "parseaut.cc"
    break;

  case 54: // properties: properties "identifier"
#line 894 "parseaut.yy"
              {
                bool val = true;
                // no-univ-branch was replaced by !univ-branch in HOA 1.1
                if (*(yystack_[0].value.str) == "no-univ-branch")
                  {
                    *(yystack_[0].value.str) = "univ-branch";
                    val = false;
                  }
		auto pos = res.props.emplace(*(yystack_[0].value.str), result_::prop_info{yystack_[0].location, val});
		if (pos.first->second.val != val)
		  {
		    std::ostringstream out(std::ios_base::ate);
		    error(yystack_[0].location, "'properties: "s + (val ? "" : "!")
                          + *(yystack_[0].value.str) + "' contradicts...");
		    error(pos.first->second.loc,
			  "... 'properties: "s + (val ? "!" : "") + *(yystack_[0].value.str)
			  + "' previously given here.");
		  }
		delete (yystack_[0].value.str);
	      }
#line 1706 "parseaut.cc"
    break;

  case 55: // properties: properties '!' "identifier"
#line 915 "parseaut.yy"
              {
		auto loc = yystack_[1].location + yystack_[0].location;
		auto pos =
		  res.props.emplace(*(yystack_[0].value.str), result_::prop_info{loc, false});
		if (pos.first->second.val)
		  {
		    std::ostringstream out(std::ios_base::ate);
		    error(loc, "'properties: !"s + *(yystack_[0].value.str) + "' contradicts...");
		    error(pos.first->second.loc, "... 'properties: "s + *(yystack_[0].value.str)
                          + "' previously given here.");
		  }
		delete (yystack_[0].value.str);
	      }
#line 1724 "parseaut.cc"
    break;

  case 57: // highlight-edges: highlight-edges "integer" "integer"
#line 931 "parseaut.yy"
              {
		res.highlight_edges->emplace((yystack_[1].value.num), (yystack_[0].value.num));
	      }
#line 1732 "parseaut.cc"
    break;

  case 59: // highlight-states: highlight-states "integer" "integer"
#line 936 "parseaut.yy"
              {
		res.highlight_states->emplace((yystack_[1].value.num), (yystack_[0].value.num));
	      }
#line 1740 "parseaut.cc"
    break;

  case 61: // state-player: state-player "integer"
#line 942 "parseaut.yy"
              {
                if ((yystack_[0].value.num) != 0 && (yystack_[0].value.num) != 1)
                  error(yystack_[0].location, "player should be 0 or 1");
                res.state_player->emplace_back((yystack_[0].value.num));
	      }
#line 1750 "parseaut.cc"
    break;

  case 65: // header-spec: header-spec "string"
#line 952 "parseaut.yy"
               {
		 delete (yystack_[0].value.str);
	       }
#line 1758 "parseaut.cc"
    break;

  case 66: // header-spec: header-spec "identifier"
#line 956 "parseaut.yy"
               {
		 delete (yystack_[0].value.str);
	       }
#line 1766 "parseaut.cc"
    break;

  case 67: // state-conj-2: checked-state-num '&' checked-state-num
#line 961 "parseaut.yy"
            {
              (yylhs.value.states) = new std::vector<unsigned>{(yystack_[2].value.num), (yystack_[0].value.num)};
            }
#line 1774 "parseaut.cc"
    break;

  case 68: // state-conj-2: state-conj-2 '&' checked-state-num
#line 965 "parseaut.yy"
            {
              (yylhs.value.states) = (yystack_[2].value.states);
              (yylhs.value.states)->emplace_back((yystack_[0].value.num));
            }
#line 1783 "parseaut.cc"
    break;

  case 69: // init-state-conj-2: state-num '&' state-num
#line 973 "parseaut.yy"
            {
              (yylhs.value.states) = new std::vector<unsigned>{(yystack_[2].value.num), (yystack_[0].value.num)};
            }
#line 1791 "parseaut.cc"
    break;

  case 70: // init-state-conj-2: init-state-conj-2 '&' state-num
#line 977 "parseaut.yy"
            {
              (yylhs.value.states) = (yystack_[2].value.states);
              (yylhs.value.states)->emplace_back((yystack_[0].value.num));
            }
#line 1800 "parseaut.cc"
    break;

  case 71: // label-expr: 't'
#line 983 "parseaut.yy"
            {
	      (yylhs.value.b) = bddtrue.id();
	    }
#line 1808 "parseaut.cc"
    break;

  case 72: // label-expr: 'f'
#line 987 "parseaut.yy"
            {
	      (yylhs.value.b) = bddfalse.id();
	    }
#line 1816 "parseaut.cc"
    break;

  case 73: // label-expr: "integer"
#line 991 "parseaut.yy"
            {
              if (res.in_alias && !res.ignore_more_ap)
                {
                  // We are reading Alias: before AP: has been given.
                  // Use $1 as temporary variable number.  We will relabel
                  // everything once AP: is known.
                  if (res.unknown_ap_max < (int)(yystack_[0].value.num))
                    {
                      res.unknown_ap_max = (yystack_[0].value.num);
                      res.unknown_ap_max_location = yystack_[0].location;
                      int missing_vars = 1 + bdd_varnum() - (yystack_[0].value.num);
                      if (missing_vars > 0)
                        bdd_extvarnum(missing_vars);
                    }
                  (yylhs.value.b) = bdd_ithvar((yystack_[0].value.num)).id();
                }
	      else if ((yystack_[0].value.num) >= res.ap.size())
		{
		  error(yystack_[0].location, "AP number is larger than the number of APs...");
		  error(res.ap_loc, "... declared here");
		  (yylhs.value.b) = bddtrue.id();
		}
	      else
		{
		  (yylhs.value.b) = bdd_ithvar(res.ap[(yystack_[0].value.num)]).id();
		  bdd_addref((yylhs.value.b));
		}
	    }
#line 1849 "parseaut.cc"
    break;

  case 74: // label-expr: "alias name"
#line 1020 "parseaut.yy"
            {
	      auto i = res.alias.find(*(yystack_[0].value.str));
	      if (i == res.alias.end())
		{
		  error(yylhs.location, "unknown alias @" + *(yystack_[0].value.str));
		  (yylhs.value.b) = 1;
		}
	      else
		{
		  (yylhs.value.b) = i->second.id();
		  bdd_addref((yylhs.value.b));
		}
	      delete (yystack_[0].value.str);
	    }
#line 1868 "parseaut.cc"
    break;

  case 75: // label-expr: '!' label-expr
#line 1035 "parseaut.yy"
            {
              (yylhs.value.b) = bdd_not((yystack_[0].value.b));
              bdd_delref((yystack_[0].value.b));
              bdd_addref((yylhs.value.b));
            }
#line 1878 "parseaut.cc"
    break;

  case 76: // label-expr: label-expr '&' label-expr
#line 1041 "parseaut.yy"
            {
              (yylhs.value.b) = bdd_and((yystack_[2].value.b), (yystack_[0].value.b));
              bdd_delref((yystack_[2].value.b));
              bdd_delref((yystack_[0].value.b));
              bdd_addref((yylhs.value.b));
            }
#line 1889 "parseaut.cc"
    break;

  case 77: // label-expr: label-expr '|' label-expr
#line 1048 "parseaut.yy"
            {
              (yylhs.value.b) = bdd_or((yystack_[2].value.b), (yystack_[0].value.b));
              bdd_delref((yystack_[2].value.b));
              bdd_delref((yystack_[0].value.b));
              bdd_addref((yylhs.value.b));
            }
#line 1900 "parseaut.cc"
    break;

  case 78: // label-expr: '(' label-expr ')'
#line 1055 "parseaut.yy"
          {
	    (yylhs.value.b) = (yystack_[1].value.b);
	  }
#line 1908 "parseaut.cc"
    break;

  case 79: // acc-set: "integer"
#line 1061 "parseaut.yy"
            {
	      if ((int) (yystack_[0].value.num) >= res.accset)
		{
		  if (!res.ignore_acc)
		    {
		      error(yystack_[0].location, "number is larger than the count "
			    "of acceptance sets...");
		      error(res.accset_loc, "... declared here.");
		    }
		  (yylhs.value.num) = -1U;
		}
	      else
		{
		  (yylhs.value.num) = (yystack_[0].value.num);
		}
	    }
#line 1929 "parseaut.cc"
    break;

  case 80: // acceptance-cond: "identifier" '(' acc-set ')'
#line 1079 "parseaut.yy"
                 {
		   if ((yystack_[1].value.num) != -1U)
		     {
		       res.pos_acc_sets |= res.aut_or_ks->acc().mark((yystack_[1].value.num));
		       if (*(yystack_[3].value.str) == "Inf")
                         {
                           (yylhs.value.code) = new spot::acc_cond::acc_code
                             (res.aut_or_ks->acc().inf({(yystack_[1].value.num)}));
                         }
		       else if (*(yystack_[3].value.str) == "Fin")
                         {
                           (yylhs.value.code) = new spot::acc_cond::acc_code
                             (res.aut_or_ks->acc().fin({(yystack_[1].value.num)}));
                         }
                       else
                         {
                           error(yystack_[3].location, "unknown acceptance '"s + *(yystack_[3].value.str)
                                 + "', expected Fin or Inf");
                           (yylhs.value.code) = new spot::acc_cond::acc_code;
                         }
		     }
		   else
		     {
		       (yylhs.value.code) = new spot::acc_cond::acc_code;
		     }
		   delete (yystack_[3].value.str);
		 }
#line 1961 "parseaut.cc"
    break;

  case 81: // acceptance-cond: "identifier" '(' '!' acc-set ')'
#line 1107 "parseaut.yy"
                 {
		   if ((yystack_[1].value.num) != -1U)
		     {
		       res.neg_acc_sets |= res.aut_or_ks->acc().mark((yystack_[1].value.num));
		       if (*(yystack_[4].value.str) == "Inf")
			 (yylhs.value.code) = new spot::acc_cond::acc_code
			   (res.aut_or_ks->acc().inf_neg({(yystack_[1].value.num)}));
		       else
			 (yylhs.value.code) = new spot::acc_cond::acc_code
			   (res.aut_or_ks->acc().fin_neg({(yystack_[1].value.num)}));
		     }
		   else
		     {
		       (yylhs.value.code) = new spot::acc_cond::acc_code;
		     }
		   delete (yystack_[4].value.str);
		 }
#line 1983 "parseaut.cc"
    break;

  case 82: // acceptance-cond: '(' acceptance-cond ')'
#line 1125 "parseaut.yy"
                 {
		   (yylhs.value.code) = (yystack_[1].value.code);
		 }
#line 1991 "parseaut.cc"
    break;

  case 83: // acceptance-cond: acceptance-cond '&' acceptance-cond
#line 1129 "parseaut.yy"
                 {
		   *(yystack_[0].value.code) &= std::move(*(yystack_[2].value.code));
		   (yylhs.value.code) = (yystack_[0].value.code);
		   delete (yystack_[2].value.code);
		 }
#line 2001 "parseaut.cc"
    break;

  case 84: // acceptance-cond: acceptance-cond '|' acceptance-cond
#line 1135 "parseaut.yy"
                 {
		   *(yystack_[0].value.code) |= std::move(*(yystack_[2].value.code));
		   (yylhs.value.code) = (yystack_[0].value.code);
		   delete (yystack_[2].value.code);
		 }
#line 2011 "parseaut.cc"
    break;

  case 85: // acceptance-cond: 't'
#line 1141 "parseaut.yy"
                 {
		   (yylhs.value.code) = new spot::acc_cond::acc_code;
		 }
#line 2019 "parseaut.cc"
    break;

  case 86: // acceptance-cond: 'f'
#line 1145 "parseaut.yy"
               {
	         {
		   (yylhs.value.code) = new spot::acc_cond::acc_code
		     (res.aut_or_ks->acc().fin({}));
		 }
	       }
#line 2030 "parseaut.cc"
    break;

  case 87: // body: states
#line 1154 "parseaut.yy"
      {
	for (auto& p: res.start)
          for (unsigned s: p.second)
            if (s >= res.info_states.size() || !res.info_states[s].declared)
              {
                error(p.first, "initial state " + std::to_string(s) +
                      " has no definition");
                // Pretend that the state is declared so we do not
                // mention it in the next loop.
                if (s < res.info_states.size())
                  res.info_states[s].declared = true;
                res.complete = spot::trival::maybe();
              }
	unsigned n = res.info_states.size();
	// States with number above res.states have already caused a
	// diagnostic, so let not add another one.
	if (res.states >= 0)
	  n = res.states;
	for (unsigned i = 0; i < n; ++i)
	  {
	    auto& p = res.info_states[i];
            if (!p.declared)
              {
                if (p.used)
                  error(p.used_loc,
                        "state " + std::to_string(i) + " has no definition");
                if (!p.used && res.complete)
                  if (auto p = res.prop_is_true("complete"))
                    {
                      error(res.states_loc,
                            "state " + std::to_string(i) +
                            " has no definition...");
                      error(p.loc, "... despite 'properties: complete'");
                    }
                res.complete = false;
              }
	  }
        if (res.complete)
          if (auto p = res.prop_is_false("complete"))
            {
              error(yystack_[0].location, "automaton is complete...");
              error(p.loc, "... despite 'properties: !complete'");
            }
        bool det_warned = false;
        if (res.universal && res.existential)
          if (auto p = res.prop_is_false("deterministic"))
            {
              error(yystack_[0].location, "automaton is deterministic...");
              error(p.loc, "... despite 'properties: !deterministic'");
              det_warned = true;
            }
        static bool tolerant = getenv("SPOT_HOA_TOLERANT");
        if (res.universal.is_true() && !det_warned && !tolerant)
          if (auto p = res.prop_is_true("exist-branch"))
            {
              error(yystack_[0].location, "automaton has no existential branching...");
              error(p.loc, "... despite 'properties: exist-branch'\n"
                    "note: If this is an issue you cannot fix, you may disable "
                    "this diagnostic\n      by defining the SPOT_HOA_TOLERANT "
                    "environment variable.");
              det_warned = true;
            }
        if (res.existential.is_true() && !det_warned && !tolerant)
          if (auto p = res.prop_is_true("univ-branch"))
            {
              error(yystack_[0].location, "automaton is has no universal branching...");
              error(p.loc, "... despite 'properties: univ-branch'\n"
                    "note: If this is an issue you cannot fix, you may disable "
                    "this diagnostic\n      by defining the SPOT_HOA_TOLERANT "
                    "environment variable.");
              det_warned = true;
            }
        if (res.state_player)
          if (unsigned spsz = res.state_player->size(); spsz != n)
            {
              error(res.state_player_loc,
                    "ignoring state-player header because it has "s
                    + std::to_string(spsz) + " entries while automaton has "
                    + std::to_string(n) + " states");
              delete res.state_player;
              res.state_player = nullptr;
            }
      }
#line 2118 "parseaut.cc"
    break;

  case 88: // state-num: "integer"
#line 1238 "parseaut.yy"
           {
	     if (((int) (yystack_[0].value.num)) < 0)
	       {
		 error(yystack_[0].location, "state number is too large for this implementation");
		 YYABORT;
	       }
	     (yylhs.value.num) = (yystack_[0].value.num);
	   }
#line 2131 "parseaut.cc"
    break;

  case 89: // checked-state-num: state-num
#line 1248 "parseaut.yy"
                   {
		     if ((int) (yystack_[0].value.num) >= res.states)
		       {
			 if (res.states >= 0)
			   {
			     error(yystack_[0].location, "state number is larger than state "
				   "count...");
			     error(res.states_loc, "... declared here.");
			   }
			 if (res.opts.want_kripke)
			   {
			     int missing =
			       ((int) (yystack_[0].value.num)) - res.h->ks->num_states() + 1;
			     if (missing >= 0)
			       {
				 res.h->ks->new_states(missing, bddfalse);
				 res.info_states.resize
				   (res.info_states.size() + missing);
			       }
			   }
			 else
			   {
			     int missing =
			       ((int) (yystack_[0].value.num)) - res.h->aut->num_states() + 1;
			     if (missing >= 0)
			       {
				 res.h->aut->new_states(missing);
				 res.info_states.resize
				   (res.info_states.size() + missing);
			       }
			   }
		       }
		     // Remember the first place were a state is the
		     // destination of a transition.
		     if (!res.info_states[(yystack_[0].value.num)].used)
		       {
			 res.info_states[(yystack_[0].value.num)].used = true;
			 res.info_states[(yystack_[0].value.num)].used_loc = yystack_[0].location;
		       }
		     (yylhs.value.num) = (yystack_[0].value.num);
		   }
#line 2177 "parseaut.cc"
    break;

  case 91: // states: states state
#line 1292 "parseaut.yy"
        {
	  if ((res.universal.is_true() || res.complete.is_true()))
	    {
	      bdd available = bddtrue;
	      bool det = true;
	      for (auto& t: res.h->aut->out(res.cur_state))
		{
		  if (det && !bdd_implies(t.cond, available))
		    det = false;
		  available -= t.cond;
		}
	      if (res.universal.is_true() && !det)
		{
		  res.universal = false;
		  if (auto p = res.prop_is_true("deterministic"))
		    {
		      error(yystack_[0].location, "automaton is not deterministic...");
		      error(p.loc,
			    "... despite 'properties: deterministic'");
		    }
		  else if (auto p = res.prop_is_false("exist-branch"))
		    {
		      error(yystack_[0].location, "automaton has existential branching...");
		      error(p.loc,
			    "... despite 'properties: !exist-branch'");
		    }
		}
	      if (res.complete.is_true() && available != bddfalse)
		{
		  res.complete = false;
		  if (auto p = res.prop_is_true("complete"))
		    {
		      error(yystack_[0].location, "automaton is not complete...");
		      error(p.loc, "... despite 'properties: complete'");
		    }
		}
	    }
	}
#line 2220 "parseaut.cc"
    break;

  case 93: // state: state-name unlabeled-edges
#line 1332 "parseaut.yy"
       {
	 if (!res.has_state_label) // Implicit labels
	   {
	     if (res.cur_guard != res.guards.end())
	       error(yylhs.location, "not enough transitions for this state");

	     if (res.label_style == State_Labels)
	       {
		 error(yystack_[0].location, "these transitions have implicit labels but the"
		       " automaton is...");
		 error(res.props["state-labels"].loc, "... declared with "
		       "'properties: state-labels'");
		 // Do not repeat this message.
		 res.label_style = Mixed_Labels;
	       }
	     res.cur_guard = res.guards.begin();
	   }
	 else if (res.opts.want_kripke)
	   {
	     res.h->ks->state_from_number(res.cur_state)->cond(res.state_label);
	   }

       }
#line 2248 "parseaut.cc"
    break;

  case 94: // state: error
#line 1356 "parseaut.yy"
       {
	 // Assume the worse.  This skips the tests about determinism
	 // we might perform on the state.
	 res.universal = spot::trival::maybe();
	 res.existential = spot::trival::maybe();
	 res.complete = spot::trival::maybe();
       }
#line 2260 "parseaut.cc"
    break;

  case 95: // state-name: "State:" state-label_opt checked-state-num string_opt state-acc_opt
#line 1366 "parseaut.yy"
          {
	    res.cur_state = (yystack_[2].value.num);
	    if (res.info_states[(yystack_[2].value.num)].declared)
	      {
		std::ostringstream o;
		o << "redeclaration of state " << (yystack_[2].value.num);
		error(yystack_[4].location + yystack_[2].location, o.str());
                // The additional transitions from extra states might
                // led us to believe that the automaton is complete
                // while it is not if we ignore them.
                if (res.complete.is_true())
                  res.complete = spot::trival::maybe();
	      }
	    res.info_states[(yystack_[2].value.num)].declared = true;
	    res.acc_state = (yystack_[0].value.mark);
	    if ((yystack_[1].value.str))
	      {
		if (!res.state_names)
		  res.state_names =
		    new std::vector<std::string>(res.states > 0 ?
						 res.states : 0);
		if (res.state_names->size() < (yystack_[2].value.num) + 1)
		  res.state_names->resize((yystack_[2].value.num) + 1);
		(*res.state_names)[(yystack_[2].value.num)] = std::move(*(yystack_[1].value.str));
		delete (yystack_[1].value.str);
	      }
	    if (res.opts.want_kripke && !res.has_state_label)
	      error(yylhs.location, "Kripke structures should have labeled states");
	  }
#line 2294 "parseaut.cc"
    break;

  case 96: // label: '[' label-expr ']'
#line 1396 "parseaut.yy"
           {
             res.cur_label = bdd_from_int((yystack_[1].value.b));
             bdd_delref((yystack_[1].value.b));
             if ((yystack_[2].value.str))
               res.fcache[*(yystack_[2].value.str)] = res.cur_label;
             delete (yystack_[2].value.str);
	   }
#line 2306 "parseaut.cc"
    break;

  case 97: // label: BDD
#line 1403 "parseaut.yy"
           { res.cur_label = bdd_from_int((yystack_[0].value.b)); }
#line 2312 "parseaut.cc"
    break;

  case 98: // label: '[' error ']'
#line 1405 "parseaut.yy"
           {
	     error(yylhs.location, "ignoring this invalid label");
	     res.cur_label = bddtrue;
             delete (yystack_[2].value.str);
	   }
#line 2322 "parseaut.cc"
    break;

  case 99: // state-label_opt: %empty
#line 1410 "parseaut.yy"
                        { res.has_state_label = false; }
#line 2328 "parseaut.cc"
    break;

  case 100: // state-label_opt: label
#line 1412 "parseaut.yy"
               {
		 res.has_state_label = true;
		 res.state_label_loc = yystack_[0].location;
		 res.state_label = res.cur_label;
		 if (res.label_style == Trans_Labels
		     || res.label_style == Implicit_Labels)
		   {
		     error(yylhs.location,
			   "state label used although the automaton was...");
		     if (res.label_style == Trans_Labels)
		       error(res.props["trans-labels"].loc,
			     "... declared with 'properties: trans-labels'"
			     " here");
		     else
		       error(res.props["implicit-labels"].loc,
			     "... declared with 'properties: implicit-labels'"
			     " here");
		     // Do not show this error anymore.
		     res.label_style = Mixed_Labels;
		   }
	       }
#line 2354 "parseaut.cc"
    break;

  case 101: // trans-label: label
#line 1434 "parseaut.yy"
                 {
		   if (res.has_state_label)
		     {
		       error(yystack_[0].location, "cannot label this edge because...");
		       error(res.state_label_loc,
			     "... the state is already labeled.");
		       res.cur_label = res.state_label;
		     }
		   if (res.label_style == State_Labels
		       || res.label_style == Implicit_Labels)
		     {
		       error(yylhs.location, "transition label used although the "
			     "automaton was...");
		       if (res.label_style == State_Labels)
			 error(res.props["state-labels"].loc,
			       "... declared with 'properties: state-labels' "
			       "here");
		       else
			 error(res.props["implicit-labels"].loc,
			       "... declared with 'properties: implicit-labels'"
			       " here");
		       // Do not show this error anymore.
		       res.label_style = Mixed_Labels;
		     }
		 }
#line 2384 "parseaut.cc"
    break;

  case 102: // acc-sig: '{' acc-sets '}'
#line 1461 "parseaut.yy"
             {
	       (yylhs.value.mark) = (yystack_[1].value.mark);
	       if (res.ignore_acc && !res.ignore_acc_silent)
		 {
		   error(yylhs.location, "ignoring acceptance sets because of "
			 "missing acceptance condition");
		   // Emit this message only once.
		   res.ignore_acc_silent = true;
		 }
	     }
#line 2399 "parseaut.cc"
    break;

  case 103: // acc-sig: '{' error '}'
#line 1472 "parseaut.yy"
             {
	       error(yylhs.location, "ignoring this invalid acceptance set");
	     }
#line 2407 "parseaut.cc"
    break;

  case 104: // acc-sets: %empty
#line 1476 "parseaut.yy"
          {
	    (yylhs.value.mark) = spot::acc_cond::mark_t({});
	  }
#line 2415 "parseaut.cc"
    break;

  case 105: // acc-sets: acc-sets acc-set
#line 1480 "parseaut.yy"
          {
	    if (res.ignore_acc || (yystack_[0].value.num) == -1U)
	      (yylhs.value.mark) = spot::acc_cond::mark_t({});
	    else
	      (yylhs.value.mark) = (yystack_[1].value.mark) | res.aut_or_ks->acc().mark((yystack_[0].value.num));
	  }
#line 2426 "parseaut.cc"
    break;

  case 106: // state-acc_opt: %empty
#line 1488 "parseaut.yy"
               {
                 (yylhs.value.mark) = spot::acc_cond::mark_t({});
               }
#line 2434 "parseaut.cc"
    break;

  case 107: // state-acc_opt: acc-sig
#line 1492 "parseaut.yy"
               {
		 (yylhs.value.mark) = (yystack_[0].value.mark);
		 if (res.acc_style == Trans_Acc)
		   {
		     error(yylhs.location, "state-based acceptance used despite...");
		     error(res.props["trans-acc"].loc,
			   "... declaration of transition-based acceptance.");
		     res.acc_style = Mixed_Acc;
		   }
	       }
#line 2449 "parseaut.cc"
    break;

  case 108: // trans-acc_opt: %empty
#line 1503 "parseaut.yy"
               {
                 (yylhs.value.mark) = spot::acc_cond::mark_t({});
               }
#line 2457 "parseaut.cc"
    break;

  case 109: // trans-acc_opt: acc-sig
#line 1507 "parseaut.yy"
               {
		 (yylhs.value.mark) = (yystack_[0].value.mark);
		 res.trans_acc_seen = true;
		 if (res.acc_style == State_Acc)
		   {
		     error(yylhs.location, "trans-based acceptance used despite...");
		     error(res.props["state-acc"].loc,
			   "... declaration of state-based acceptance.");
		     res.acc_style = Mixed_Acc;
		   }
	       }
#line 2473 "parseaut.cc"
    break;

  case 115: // incorrectly-unlabeled-edge: checked-state-num trans-acc_opt
#line 1526 "parseaut.yy"
                            {
			      bdd cond = bddtrue;
			      if (!res.has_state_label)
				error(yylhs.location, "missing label for this edge "
				      "(previous edge is labeled)");
			      else
				cond = res.state_label;
			      if (cond != bddfalse)
				{
				  if (res.opts.want_kripke)
				    res.h->ks->new_edge(res.cur_state, (yystack_[1].value.num));
				  else
				    res.h->aut->new_edge(res.cur_state, (yystack_[1].value.num),
							 cond,
							 (yystack_[0].value.mark) | res.acc_state);
				}
			    }
#line 2495 "parseaut.cc"
    break;

  case 116: // labeled-edge: trans-label checked-state-num trans-acc_opt
#line 1544 "parseaut.yy"
              {
		if (res.cur_label != bddfalse)
		  {
		    if (res.opts.want_kripke)
		      res.h->ks->new_edge(res.cur_state, (yystack_[1].value.num));
		    else
		      res.h->aut->new_edge(res.cur_state, (yystack_[1].value.num),
					   res.cur_label, (yystack_[0].value.mark) | res.acc_state);
		  }
	      }
#line 2510 "parseaut.cc"
    break;

  case 117: // labeled-edge: trans-label state-conj-checked trans-acc_opt
#line 1555 "parseaut.yy"
              {
                if (res.cur_label != bddfalse)
                  {
                    assert(!res.opts.want_kripke);
                    res.h->aut->new_univ_edge(res.cur_state,
                                              (yystack_[1].value.states)->begin(), (yystack_[1].value.states)->end(),
                                              res.cur_label,
                                              (yystack_[0].value.mark) | res.acc_state);
                  }
                delete (yystack_[1].value.states);
	      }
#line 2526 "parseaut.cc"
    break;

  case 118: // state-conj-checked: state-conj-2
#line 1568 "parseaut.yy"
              {
                (yylhs.value.states) = (yystack_[0].value.states);
                if (auto ub = res.prop_is_false("univ-branch"))
                  {
                    error(yystack_[0].location, "universal branch used despite"
                          " previous declaration...");
                    error(ub.loc, "... here");
                  }
                res.existential = false;
              }
#line 2541 "parseaut.cc"
    break;

  case 122: // unlabeled-edge: checked-state-num trans-acc_opt
#line 1586 "parseaut.yy"
                {
		  bdd cond;
		  if (res.has_state_label)
		    {
		      cond = res.state_label;
		    }
		  else
		    {
		      if (res.guards.empty())
			fill_guards(res);
		      if (res.cur_guard == res.guards.end())
			{
			  error(yylhs.location, "too many transitions for this state, "
				"ignoring this one");
			  cond = bddfalse;
			}
		      else
			{
			  cond = *res.cur_guard++;
			}
		    }
		  if (cond != bddfalse)
		    {
		      if (res.opts.want_kripke)
			res.h->ks->new_edge(res.cur_state, (yystack_[1].value.num));
		      else
			res.h->aut->new_edge(res.cur_state, (yystack_[1].value.num),
					     cond, (yystack_[0].value.mark) | res.acc_state);
		    }
		}
#line 2576 "parseaut.cc"
    break;

  case 123: // unlabeled-edge: state-conj-checked trans-acc_opt
#line 1617 "parseaut.yy"
                {
		  bdd cond;
		  if (res.has_state_label)
		    {
		      cond = res.state_label;
		    }
		  else
		    {
		      if (res.guards.empty())
			fill_guards(res);
		      if (res.cur_guard == res.guards.end())
			{
			  error(yylhs.location, "too many transitions for this state, "
				"ignoring this one");
			  cond = bddfalse;
			}
		      else
			{
			  cond = *res.cur_guard++;
			}
		    }
		  if (cond != bddfalse)
		    {
		      assert(!res.opts.want_kripke);
                      res.h->aut->new_univ_edge(res.cur_state,
                                                (yystack_[1].value.states)->begin(), (yystack_[1].value.states)->end(),
                                                cond, (yystack_[0].value.mark) | res.acc_state);
		    }
                  delete (yystack_[1].value.states);
		}
#line 2611 "parseaut.cc"
    break;

  case 124: // incorrectly-labeled-edge: trans-label unlabeled-edge
#line 1648 "parseaut.yy"
                          {
			    error(yystack_[1].location, "ignoring this label, because previous"
				  " edge has no label");
                          }
#line 2620 "parseaut.cc"
    break;

  case 126: // dstar: dstar_type error "end of DSTAR automaton"
#line 1660 "parseaut.yy"
       {
	 error(yylhs.location, "failed to parse this as an ltl2dstar automaton");
       }
#line 2628 "parseaut.cc"
    break;

  case 127: // dstar_type: "DRA"
#line 1665 "parseaut.yy"
       {
         res.h->type = spot::parsed_aut_type::DRA;
         res.plus = 1;
         res.minus = 0;
	 if (res.opts.want_kripke)
	   {
	     error(yylhs.location,
		   "cannot read a Kripke structure out of a DSTAR automaton");
	     YYABORT;
	   }
       }
#line 2644 "parseaut.cc"
    break;

  case 128: // dstar_type: "DSA"
#line 1677 "parseaut.yy"
       {
	 res.h->type = spot::parsed_aut_type::DSA;
         res.plus = 0;
         res.minus = 1;
	 if (res.opts.want_kripke)
	   {
	     error(yylhs.location,
		   "cannot read a Kripke structure out of a DSTAR automaton");
	     YYABORT;
	   }
       }
#line 2660 "parseaut.cc"
    break;

  case 129: // dstar_header: dstar_sizes
#line 1690 "parseaut.yy"
  {
    if (res.states < 0)
      error(yystack_[0].location, "missing state count");
    if (!res.ignore_more_acc)
      error(yystack_[0].location, "missing acceptance-pair count");
    if (res.start.empty())
      error(yystack_[0].location, "missing start-state number");
    if (!res.ignore_more_ap)
      error(yystack_[0].location, "missing atomic propositions definition");

    if (res.states > 0)
      {
	res.h->aut->new_states(res.states);;
	res.info_states.resize(res.states);
      }
    res.acc_style = State_Acc;
    res.universal = true;
    res.existential = true;
    res.complete = true;
    fill_guards(res);
    res.cur_guard = res.guards.end();
  }
#line 2687 "parseaut.cc"
    break;

  case 132: // dstar_sizes: dstar_sizes "Acceptance-Pairs:" "integer"
#line 1716 "parseaut.yy"
  {
    if (res.ignore_more_acc)
      {
	error(yystack_[2].location + yystack_[1].location, "ignoring this redefinition of the "
	      "acceptance pairs...");
	error(res.accset_loc, "... previously defined here.");
      }
    else{
      res.accset = (yystack_[0].value.num);
      res.h->aut->set_acceptance(2 * (yystack_[0].value.num),
				 res.h->type == spot::parsed_aut_type::DRA
				 ? spot::acc_cond::acc_code::rabin((yystack_[0].value.num))
				 : spot::acc_cond::acc_code::streett((yystack_[0].value.num)));
      res.accset_loc = yystack_[0].location;
      res.ignore_more_acc = true;
    }
  }
#line 2709 "parseaut.cc"
    break;

  case 133: // dstar_sizes: dstar_sizes "States:" "integer"
#line 1734 "parseaut.yy"
  {
    if (res.states < 0)
      {
	res.states = (yystack_[0].value.num);
      }
    else
      {
	error(yylhs.location, "redeclaration of state count");
	if ((unsigned) res.states < (yystack_[0].value.num))
	  res.states = (yystack_[0].value.num);
      }
  }
#line 2726 "parseaut.cc"
    break;

  case 134: // dstar_sizes: dstar_sizes "Start:" "integer"
#line 1747 "parseaut.yy"
  {
    res.start.emplace_back(yystack_[0].location, std::vector<unsigned>{(yystack_[0].value.num)});
  }
#line 2734 "parseaut.cc"
    break;

  case 136: // dstar_state_id: "State:" "integer" string_opt
#line 1753 "parseaut.yy"
  {
    if (res.cur_guard != res.guards.end())
      error(yystack_[2].location, "not enough transitions for previous state");
    if (res.states < 0 || (yystack_[1].value.num) >= (unsigned) res.states)
      {
	std::ostringstream o;
	if (res.states > 0)
	  {
	    o << "state numbers should be in the range [0.."
	      << res.states - 1 << "]";
	  }
	else
	  {
	    o << "no states have been declared";
	  }
	error(yystack_[1].location, o.str());
      }
    else
      {
	res.info_states[(yystack_[1].value.num)].declared = true;

	if ((yystack_[0].value.str))
	  {
	    if (!res.state_names)
	      res.state_names =
		new std::vector<std::string>(res.states > 0 ?
					     res.states : 0);
	    if (res.state_names->size() < (yystack_[1].value.num) + 1)
	      res.state_names->resize((yystack_[1].value.num) + 1);
	    (*res.state_names)[(yystack_[1].value.num)] = std::move(*(yystack_[0].value.str));
	    delete (yystack_[0].value.str);
	  }
      }

    res.cur_guard = res.guards.begin();
    res.dest_map.clear();
    res.cur_state = (yystack_[1].value.num);
  }
#line 2777 "parseaut.cc"
    break;

  case 137: // sign: '+'
#line 1792 "parseaut.yy"
          { (yylhs.value.num) = res.plus; }
#line 2783 "parseaut.cc"
    break;

  case 138: // sign: '-'
#line 1793 "parseaut.yy"
          { (yylhs.value.num) = res.minus; }
#line 2789 "parseaut.cc"
    break;

  case 139: // dstar_accsigs: %empty
#line 1797 "parseaut.yy"
  {
    (yylhs.value.mark) = spot::acc_cond::mark_t({});
  }
#line 2797 "parseaut.cc"
    break;

  case 140: // dstar_accsigs: dstar_accsigs sign "integer"
#line 1801 "parseaut.yy"
  {
    if (res.states < 0 || res.cur_state >= (unsigned) res.states)
      break;
    if (res.accset > 0 && (yystack_[0].value.num) < (unsigned) res.accset)
      {
	(yylhs.value.mark) = (yystack_[2].value.mark);
	(yylhs.value.mark).set((yystack_[0].value.num) * 2 + (yystack_[1].value.num));
      }
    else
      {
	std::ostringstream o;
	if (res.accset > 0)
	  {
	    o << "acceptance pairs should be in the range [0.."
	      << res.accset - 1 << "]";
	  }
	else
	  {
	    o << "no acceptance pairs have been declared";
	  }
	error(yystack_[0].location, o.str());
      }
  }
#line 2825 "parseaut.cc"
    break;

  case 141: // dstar_state_accsig: "Acc-Sig:" dstar_accsigs
#line 1825 "parseaut.yy"
                                             { (yylhs.value.mark) = (yystack_[0].value.mark); }
#line 2831 "parseaut.cc"
    break;

  case 143: // dstar_transitions: dstar_transitions "integer"
#line 1829 "parseaut.yy"
  {
    std::pair<map_t::iterator, bool> i =
      res.dest_map.emplace((yystack_[0].value.num), *res.cur_guard);
    if (!i.second)
      i.first->second |= *res.cur_guard;
    ++res.cur_guard;
  }
#line 2843 "parseaut.cc"
    break;

  case 146: // dstar_states: dstar_states dstar_state_id dstar_state_accsig dstar_transitions
#line 1840 "parseaut.yy"
  {
    for (auto i: res.dest_map)
      res.h->aut->new_edge(res.cur_state, i.first, i.second, (yystack_[1].value.mark));
  }
#line 2852 "parseaut.cc"
    break;

  case 147: // $@9: %empty
#line 1850 "parseaut.yy"
       {
	 if (res.opts.want_kripke)
	   {
	     error(yylhs.location, "cannot read a Kripke structure out of a never claim.");
	     YYABORT;
	   }
	 res.namer = res.h->aut->create_namer<std::string>();
	 res.h->aut->set_buchi();
	 res.acc_style = State_Acc;
	 res.pos_acc_sets = res.h->aut->acc().all_sets();
       }
#line 2868 "parseaut.cc"
    break;

  case 148: // never: "never" $@9 '{' nc-states '}'
#line 1862 "parseaut.yy"
       {
	 // Add an accept_all state if needed.
	 if (res.accept_all_needed && !res.accept_all_seen)
	   {
	     unsigned n = res.namer->new_state("accept_all");
	     res.h->aut->new_acc_edge(n, n, bddtrue);
	   }
	 // If we aliased existing state, we have some unreachable
	 // states to remove.
	 if (res.aliased_states)
	   res.h->aut->purge_unreachable_states();
	 res.info_states.resize(res.h->aut->num_states());
	 // Pretend that we have declared all states.
	 for (auto& p: res.info_states)
	   p.declared = true;
         res.h->aut->register_aps_from_dict();
       }
#line 2890 "parseaut.cc"
    break;

  case 153: // nc-one-ident: "identifier" ':'
#line 1886 "parseaut.yy"
    {
      auto r = res.labels.insert(std::make_pair(*(yystack_[1].value.str), yystack_[1].location));
      if (!r.second)
	{
	  error(yystack_[1].location, "redefinition of "s + *(yystack_[1].value.str) + "...");
	  error(r.first->second, "... "s + *(yystack_[1].value.str) + " previously defined here");
	}
      (yylhs.value.str) = (yystack_[1].value.str);
    }
#line 2904 "parseaut.cc"
    break;

  case 154: // nc-ident-list: nc-one-ident
#line 1897 "parseaut.yy"
    {
      unsigned n = res.namer->new_state(*(yystack_[0].value.str));
      if (res.start.empty())
	{
	  // The first state is initial.
	  res.start.emplace_back(yylhs.location, std::vector<unsigned>{n});
	}
      (yylhs.value.str) = (yystack_[0].value.str);
    }
#line 2918 "parseaut.cc"
    break;

  case 155: // nc-ident-list: nc-ident-list nc-one-ident
#line 1907 "parseaut.yy"
    {
      res.aliased_states |=
	res.namer->alias_state(res.namer->get_state(*(yystack_[1].value.str)), *(yystack_[0].value.str));
      // Keep any identifier that starts with accept.
      if (strncmp("accept", (yystack_[1].value.str)->c_str(), 6))
        {
          delete (yystack_[1].value.str);
          (yylhs.value.str) = (yystack_[0].value.str);
        }
      else
        {
	  delete (yystack_[0].value.str);
	  (yylhs.value.str) = (yystack_[1].value.str);
        }
    }
#line 2938 "parseaut.cc"
    break;

  case 156: // nc-transition-block: "if" nc-transitions "fi"
#line 1925 "parseaut.yy"
    {
      (yylhs.value.list) = (yystack_[1].value.list);
    }
#line 2946 "parseaut.cc"
    break;

  case 157: // nc-transition-block: "do" nc-transitions "od"
#line 1929 "parseaut.yy"
    {
      (yylhs.value.list) = (yystack_[1].value.list);
    }
#line 2954 "parseaut.cc"
    break;

  case 158: // nc-state: nc-ident-list "skip"
#line 1935 "parseaut.yy"
    {
      if (*(yystack_[1].value.str) == "accept_all")
	res.accept_all_seen = true;

      auto acc = !strncmp("accept", (yystack_[1].value.str)->c_str(), 6) ?
	res.h->aut->acc().all_sets() : spot::acc_cond::mark_t({});
      res.namer->new_edge(*(yystack_[1].value.str), *(yystack_[1].value.str), bddtrue, acc);
      delete (yystack_[1].value.str);
    }
#line 2968 "parseaut.cc"
    break;

  case 159: // nc-state: nc-ident-list
#line 1944 "parseaut.yy"
                  { delete (yystack_[0].value.str); }
#line 2974 "parseaut.cc"
    break;

  case 160: // nc-state: nc-ident-list "false"
#line 1945 "parseaut.yy"
                          { delete (yystack_[1].value.str); }
#line 2980 "parseaut.cc"
    break;

  case 161: // nc-state: nc-ident-list nc-transition-block
#line 1947 "parseaut.yy"
    {
      auto acc = !strncmp("accept", (yystack_[1].value.str)->c_str(), 6) ?
	res.h->aut->acc().all_sets() : spot::acc_cond::mark_t({});
      for (auto& p: *(yystack_[0].value.list))
	{
	  bdd c = bdd_from_int(p.first);
	  bdd_delref(p.first);
	  res.namer->new_edge(*(yystack_[1].value.str), *p.second, c, acc);
	  delete p.second;
	}
      delete (yystack_[1].value.str);
      delete (yystack_[0].value.list);
    }
#line 2998 "parseaut.cc"
    break;

  case 162: // nc-transitions: %empty
#line 1962 "parseaut.yy"
         { (yylhs.value.list) = new std::list<pair>; }
#line 3004 "parseaut.cc"
    break;

  case 163: // nc-transitions: nc-transitions nc-transition
#line 1964 "parseaut.yy"
    {
      if ((yystack_[0].value.p))
	{
	  (yystack_[1].value.list)->push_back(*(yystack_[0].value.p));
	  delete (yystack_[0].value.p);
	}
      (yylhs.value.list) = (yystack_[1].value.list);
    }
#line 3017 "parseaut.cc"
    break;

  case 164: // nc-formula-or-ident: "boolean formula"
#line 1973 "parseaut.yy"
                     { (yylhs.value.str) = (yystack_[0].value.str); }
#line 3023 "parseaut.cc"
    break;

  case 165: // nc-formula-or-ident: "identifier"
#line 1973 "parseaut.yy"
                               { (yylhs.value.str) = (yystack_[0].value.str); }
#line 3029 "parseaut.cc"
    break;

  case 166: // nc-formula: nc-formula-or-ident
#line 1976 "parseaut.yy"
     {
       auto i = res.fcache.find(*(yystack_[0].value.str));
       if (i == res.fcache.end())
	 {
	   auto pf = spot::parse_infix_boolean(*(yystack_[0].value.str), *res.env, debug_level(),
					       true);
	   for (auto& j: pf.errors)
	     {
	       // Adjust the diagnostic to the current position.
	       spot::location here = yystack_[0].location;
	       here.end.line = here.begin.line + j.first.end.line - 1;
	       here.end.column = here.begin.column + j.first.end.column - 1;
	       here.begin.line += j.first.begin.line - 1;
	       here.begin.column += j.first.begin.column - 1;
	       res.h->errors.emplace_back(here, j.second);
	     }
           bdd cond = bddfalse;
	   if (pf.f)
	     cond = spot::formula_to_bdd(pf.f,
					 res.h->aut->get_dict(), res.h->aut);
	   (yylhs.value.b) = (res.fcache[*(yystack_[0].value.str)] = cond).id();
	 }
       else
	 {
	   (yylhs.value.b) = i->second.id();
	 }
       bdd_addref((yylhs.value.b));
       delete (yystack_[0].value.str);
     }
#line 3063 "parseaut.cc"
    break;

  case 167: // nc-formula: "false"
#line 2006 "parseaut.yy"
     {
       (yylhs.value.b) = 0;
     }
#line 3071 "parseaut.cc"
    break;

  case 168: // nc-opt-dest: %empty
#line 2012 "parseaut.yy"
    {
      (yylhs.value.str) = nullptr;
    }
#line 3079 "parseaut.cc"
    break;

  case 169: // nc-opt-dest: "->" "goto" "identifier"
#line 2016 "parseaut.yy"
    {
      (yylhs.value.str) = (yystack_[0].value.str);
    }
#line 3087 "parseaut.cc"
    break;

  case 170: // nc-opt-dest: "->" "assert" "boolean formula"
#line 2020 "parseaut.yy"
    {
      delete (yystack_[0].value.str);
      (yylhs.value.str) = new std::string("accept_all");
      res.accept_all_needed = true;
    }
#line 3097 "parseaut.cc"
    break;

  case 171: // nc-src-dest: nc-formula nc-opt-dest
#line 2027 "parseaut.yy"
    {
      // If there is no destination, do ignore the transition.
      // This happens for instance with
      //   if
      //   :: false
      //   fi
      if (!(yystack_[0].value.str))
	{
	  (yylhs.value.p) = nullptr;
	}
      else
	{
	  (yylhs.value.p) = new pair((yystack_[1].value.b), (yystack_[0].value.str));
	  res.namer->new_state(*(yystack_[0].value.str));
	}
    }
#line 3118 "parseaut.cc"
    break;

  case 172: // nc-transition: ':' ':' "atomic" '{' nc-src-dest '}'
#line 2046 "parseaut.yy"
    {
      (yylhs.value.p) = (yystack_[1].value.p);
    }
#line 3126 "parseaut.cc"
    break;

  case 173: // nc-transition: ':' ':' nc-src-dest
#line 2050 "parseaut.yy"
    {
      (yylhs.value.p) = (yystack_[0].value.p);
    }
#line 3134 "parseaut.cc"
    break;

  case 174: // lbtt: lbtt-header lbtt-body "-1"
#line 2059 "parseaut.yy"
      {
	auto& acc = res.h->aut->acc();
	unsigned num = acc.num_sets();
	res.h->aut->set_generalized_buchi(num);
	res.pos_acc_sets = acc.all_sets();
	assert(!res.states_map.empty());
	auto n = res.states_map.size();
	if (n != (unsigned) res.states)
	  {
	    std::ostringstream err;
	    err << res.states << " states have been declared, but "
		<< n << " different state numbers have been used";
	    error(yylhs.location, err.str());
	  }
	if (res.states_map.rbegin()->first > (unsigned) res.states)
	  {
	    // We have seen numbers larger that the total number of
	    // states in the automaton.  Usually this happens when the
	    // states are numbered from 1 instead of 0, but the LBTT
	    // documentation actually allow any number to be used.
	    // What we have done is to map all input state numbers 0
	    // <= .. < n to the digraph states with the same number,
	    // and any time we saw a number larger than n, we mapped
	    // it to a new state.  The correspondence is given by
	    // res.states_map.  Now we just need to remove the useless
	    // states we allocated.
	    std::vector<unsigned> rename(res.h->aut->num_states(), -1U);
	    unsigned s = 0;
	    for (auto& i: res.states_map)
	      rename[i.second] = s++;
	    assert(s == (unsigned) res.states);
	    for (auto& i: res.start)
	      i.second.front() = rename[i.second.front()];
	    res.h->aut->get_graph().defrag_states(rename, s);
	  }
	 res.info_states.resize(res.h->aut->num_states());
	 for (auto& s: res.info_states)
	   s.declared = true;
         res.h->aut->register_aps_from_dict();
      }
#line 3179 "parseaut.cc"
    break;

  case 175: // lbtt: lbtt-header-states "acceptance sets for empty automaton"
#line 2100 "parseaut.yy"
      {
        res.h->aut->set_generalized_buchi((yystack_[0].value.num));
	res.pos_acc_sets = res.h->aut->acc().all_sets();
      }
#line 3188 "parseaut.cc"
    break;

  case 176: // lbtt-header-states: "LBTT header"
#line 2106 "parseaut.yy"
                  {
		    if (res.opts.want_kripke)
		      {
			error(yylhs.location,
			      "cannot read a Kripke structure out of "
			      "an LBTT automaton");
			YYABORT;
		      }
		    res.states = (yystack_[0].value.num);
		    res.states_loc = yystack_[0].location;
		    res.h->aut->new_states((yystack_[0].value.num));
		  }
#line 3205 "parseaut.cc"
    break;

  case 177: // lbtt-header: lbtt-header-states "state acceptance"
#line 2119 "parseaut.yy"
           {
	     res.acc_mapper = new spot::acc_mapper_int(res.h->aut, (yystack_[0].value.num));
	     res.acc_style = State_Acc;
	   }
#line 3214 "parseaut.cc"
    break;

  case 178: // lbtt-header: lbtt-header-states "integer"
#line 2124 "parseaut.yy"
           {
	     res.acc_mapper = new spot::acc_mapper_int(res.h->aut, (yystack_[0].value.num));
	     res.trans_acc_seen = true;
	   }
#line 3223 "parseaut.cc"
    break;

  case 182: // lbtt-state: "state number" "integer" lbtt-acc
#line 2133 "parseaut.yy"
          {
	    if ((yystack_[2].value.num) >= (unsigned) res.states)
	      {
		auto p = res.states_map.emplace((yystack_[2].value.num), 0);
		if (p.second)
		  p.first->second = res.h->aut->new_state();
		res.cur_state = p.first->second;
	      }
	    else
	      {
		res.states_map.emplace((yystack_[2].value.num), (yystack_[2].value.num));
		res.cur_state = (yystack_[2].value.num);
	      }
	    if ((yystack_[1].value.num))
	      res.start.emplace_back(yystack_[2].location + yystack_[1].location,
                                     std::vector<unsigned>{res.cur_state});
	    res.acc_state = (yystack_[0].value.mark);
	  }
#line 3246 "parseaut.cc"
    break;

  case 183: // lbtt-acc: %empty
#line 2151 "parseaut.yy"
                 { (yylhs.value.mark) = spot::acc_cond::mark_t({}); }
#line 3252 "parseaut.cc"
    break;

  case 184: // lbtt-acc: lbtt-acc "acceptance set"
#line 2153 "parseaut.yy"
        {
	  (yylhs.value.mark)  = (yystack_[1].value.mark);
	  auto p = res.acc_mapper->lookup((yystack_[0].value.num));
	  if (p.first)
	    (yylhs.value.mark) |= p.second;
	  else
	    error(yystack_[0].location, "more acceptance sets used than declared");
	}
#line 3265 "parseaut.cc"
    break;

  case 185: // lbtt-guard: "string"
#line 2162 "parseaut.yy"
          {
	    auto pf = spot::parse_prefix_ltl(*(yystack_[0].value.str), *res.env);
	    if (!pf.f || !pf.errors.empty())
	      {
		std::string s = "failed to parse guard: ";
		s += *(yystack_[0].value.str);
		error(yylhs.location, s);
	      }
	    if (!pf.errors.empty())
	      for (auto& j: pf.errors)
		{
		  // Adjust the diagnostic to the current position.
		  spot::location here = yystack_[0].location;
		  here.end.line = here.begin.line + j.first.end.line - 1;
		  here.end.column = here.begin.column + j.first.end.column - 1;
		  here.begin.line += j.first.begin.line - 1;
		  here.begin.column += j.first.begin.column - 1;
		  res.h->errors.emplace_back(here, j.second);
		}
	    if (!pf.f)
	      {
		res.cur_label = bddtrue;
	      }
	    else
	      {
		if (!pf.f.is_boolean())
		  {
		    error(yylhs.location,
			  "non-Boolean transition label (replaced by true)");
		    res.cur_label = bddtrue;
		  }
		else
		  {
		    res.cur_label =
		      formula_to_bdd(pf.f, res.h->aut->get_dict(), res.h->aut);
		  }
	      }
	    delete (yystack_[0].value.str);
	  }
#line 3309 "parseaut.cc"
    break;

  case 187: // lbtt-transitions: lbtt-transitions "destination number" lbtt-acc lbtt-guard
#line 2203 "parseaut.yy"
                {
		  unsigned dst = (yystack_[2].value.num);
		  if (dst >= (unsigned) res.states)
		    {
		      auto p = res.states_map.emplace(dst, 0);
		      if (p.second)
			p.first->second = res.h->aut->new_state();
		      dst = p.first->second;
		    }
		  else
		    {
		      res.states_map.emplace(dst, dst);
		    }
		  res.h->aut->new_edge(res.cur_state, dst,
				       res.cur_label,
				       res.acc_state | (yystack_[1].value.mark));
		}
#line 3331 "parseaut.cc"
    break;


#line 3335 "parseaut.cc"

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


  const short parser::yypact_ninf_ = -171;

  const short parser::yytable_ninf_ = -130;

  const short
  parser::yypact_[] =
  {
      15,  -171,    17,   128,  -171,  -171,  -171,  -171,  -171,    23,
    -171,  -171,    14,  -171,  -171,    94,  -171,  -171,    49,  -171,
    -171,  -171,    19,    48,    15,    30,  -171,  -171,   132,    46,
      98,  -171,  -171,  -171,    68,    76,  -171,  -171,  -171,  -171,
     139,   137,   145,  -171,   140,   141,   142,   146,   147,   149,
     150,   151,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,   148,  -171,   102,   -34,  -171,    89,  -171,  -171,
    -171,    91,  -171,    99,  -171,  -171,   143,   144,  -171,  -171,
    -171,  -171,   152,  -171,    -6,  -171,  -171,  -171,    54,   153,
      85,  -171,   119,  -171,  -171,   139,  -171,  -171,  -171,  -171,
    -171,  -171,     3,  -171,  -171,   141,   154,  -171,    44,  -171,
     141,  -171,    99,  -171,   114,    99,  -171,   141,   141,  -171,
      61,    -8,    36,  -171,  -171,  -171,   158,   157,   159,   160,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,   162,   163,
     164,  -171,   127,  -171,  -171,    -3,   -23,   129,  -171,  -171,
      61,  -171,  -171,    61,    64,   152,   141,   141,     2,  -171,
    -171,    44,   114,   114,  -171,  -171,  -171,   141,  -171,  -171,
    -171,  -171,   166,   120,   133,  -171,  -171,    -8,   122,  -171,
    -171,  -171,  -171,   168,   170,  -171,    13,  -171,  -171,  -171,
    -171,    -1,  -171,   131,  -171,  -171,  -171,  -171,    53,    61,
      61,  -171,   114,  -171,  -171,   134,   -15,  -171,  -171,  -171,
    -171,  -171,  -171,   130,    75,    -8,    -8,  -171,  -171,  -171,
     171,  -171,   165,  -171,  -171,   -10,  -171,   161,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,   176,   155,  -171,   167,  -171,
     152,  -171,  -171,  -171,  -171,   138,  -171,  -171,   169,  -171,
     156,  -171,  -171,    97,   178,    59,    56,  -171,  -171,  -171,
    -171,   180,  -171,   172,   185,   173,  -171,  -171,  -171,  -171
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     5,     0,     0,   127,   128,     3,   147,   176,     0,
       2,     8,     0,    24,    11,     0,     9,    10,     0,   180,
       6,     7,     0,     0,     0,     0,     1,    90,     0,     0,
       0,   178,   177,   175,     0,   179,    13,    19,    21,     4,
     149,     0,     0,    45,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    38,    40,    42,    62,    29,    25,   126,
     130,   174,     0,   186,     0,     0,   154,   159,   150,    12,
      94,    99,    91,   110,    26,    88,    27,    28,    22,    30,
      32,    49,    14,    36,    37,    56,    58,    60,    44,     0,
       0,   183,   181,   153,   148,   152,   158,   162,   162,   160,
     155,   161,     0,    97,   100,     0,   118,    89,   108,   101,
       0,    92,   111,   112,   108,    93,   119,     0,     0,    46,
       0,     0,    34,    15,    35,    54,     0,    39,    41,    43,
      66,    65,    64,    16,    17,    63,   144,   131,     0,     0,
       0,   135,   182,   183,   151,     0,     0,     0,    74,    73,
       0,    71,    72,     0,     0,    14,     0,     0,     0,   109,
     122,   108,   108,   108,   114,   113,   123,     0,   120,   121,
      70,    69,    23,    31,     0,    85,    86,     0,    33,    52,
      51,    50,    55,     0,     0,    61,     0,   133,   134,   132,
     184,     0,   156,     0,   163,   157,    98,    75,     0,     0,
       0,    96,   106,    68,    67,     0,     0,   116,   117,   115,
     124,    48,    47,     0,     0,     0,     0,    57,    59,   145,
       0,   125,     0,   185,   187,     0,    78,    77,    76,   107,
      95,   103,    79,   102,   105,     0,     0,    82,    84,    83,
      14,   139,   142,   165,   167,     0,   164,   166,   168,   173,
       0,    80,   136,   141,   146,     0,     0,   171,    81,   137,
     138,     0,   143,     0,     0,     0,   140,   172,   169,   170
  };

  const short
  parser::yypgoto_[] =
  {
    -171,   181,  -171,   204,  -171,  -155,    86,  -171,  -171,  -171,
    -171,   117,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -119,  -130,  -170,  -171,   -43,  -100,  -171,  -171,  -171,   174,
    -171,    95,     7,  -171,  -171,   -92,  -171,  -171,  -171,   101,
     104,  -171,  -109,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,   175,  -171,  -171,
     116,   121,  -171,  -171,  -171,   -38,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,    77,  -171,  -171
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     9,    24,    10,    11,   124,   135,    12,    38,    13,
      23,    57,   119,    28,    58,   120,   121,    85,    86,    87,
     172,   212,   122,    84,   127,   128,   129,    88,   106,    76,
     154,   234,   178,    41,   107,   108,    42,    72,    73,   109,
     105,   110,   159,   206,   230,   160,   111,   112,   164,   113,
     114,   115,   116,   169,    14,    15,    89,    90,   222,   261,
     253,   242,   254,   186,    16,    25,    65,    66,    67,   101,
      68,   145,   247,   248,   257,   249,   194,    17,    18,    19,
      34,    35,    63,   142,   224,    92
  };

  const short
  parser::yytable_[] =
  {
     202,   173,    77,   205,   147,   155,   168,   214,   232,   243,
     161,   174,   163,   125,   219,     1,     2,    20,     3,   195,
       3,   223,   166,    26,   148,  -104,   149,    27,   220,    94,
     126,   197,    95,    36,   198,   244,   245,   192,   246,   150,
       4,     5,     4,     5,   193,   238,   239,     6,   233,   175,
     176,   177,     7,   190,     7,   179,   203,   204,   210,   180,
     151,   152,   153,   221,   193,  -104,     8,    37,     8,   207,
     208,   209,    31,   130,   170,   171,   131,   132,   243,   157,
     227,   228,   148,   236,   149,   252,   137,   199,   200,   138,
     139,    46,    40,   133,   134,    29,    59,   150,   199,   200,
     264,    32,    33,   265,   244,   250,   158,   246,    64,   215,
     216,   133,   134,   226,   140,   102,  -129,    61,   151,   152,
     153,    30,    75,   102,   103,   201,    60,    96,    97,    22,
      98,    62,   103,    43,    99,   237,    44,    45,    46,    47,
      48,    49,    50,    51,    52,   -18,    70,   -20,    53,    54,
      55,    69,    56,   232,   199,   200,   215,   216,    64,   -87,
      71,   259,   260,    74,    75,    78,   235,    79,    81,    93,
      80,    91,    82,    83,   123,   143,   158,   182,   117,   118,
     183,   190,   184,   185,   136,   187,   188,   189,   211,   156,
     196,   217,   213,   218,   240,   241,   200,   231,   225,   232,
     255,   262,   216,   266,   268,    39,    21,   141,   181,   229,
     167,   144,   256,   165,   162,   251,   258,   263,     0,   146,
     191,   269,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   267,     0,     0,     0,     0,
       0,     0,   100,     0,     0,   104
  };

  const short
  parser::yycheck_[] =
  {
     155,   120,    45,     1,     1,   105,   115,   177,    23,    19,
     110,    19,   112,    19,     1,     0,     1,     0,     3,    42,
       3,    22,   114,     0,    21,    23,    23,    13,    15,    63,
      36,   150,    66,    14,   153,    45,    46,    40,    48,    36,
      25,    26,    25,    26,    67,   215,   216,    32,    63,    57,
      58,    59,    37,    54,    37,    19,   156,   157,   167,    23,
      57,    58,    59,    50,    67,    63,    51,    19,    51,   161,
     162,   163,    23,    19,   117,   118,    22,    23,    19,    35,
     199,   200,    21,   213,    23,   240,     1,    34,    35,     4,
       5,     6,    62,    57,    58,     1,    50,    36,    34,    35,
      44,    52,    53,    47,    45,   235,    62,    48,    19,    34,
      35,    57,    58,    60,    29,    24,    31,    49,    57,    58,
      59,    27,    23,    24,    33,    61,    28,    38,    39,     1,
      41,    55,    33,     1,    45,    60,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     1,    19,    16,    17,
      18,    14,    20,    23,    34,    35,    34,    35,    19,    14,
      15,    64,    65,    23,    23,    23,    36,    21,    19,    67,
      23,    23,    22,    22,    22,    56,    62,    19,    35,    35,
      23,    54,    23,    23,    31,    23,    23,    23,    22,    35,
      61,    23,    59,    23,    23,    30,    35,    63,    67,    23,
      62,    23,    35,    23,    19,    24,     2,    90,   122,   202,
     115,    95,    43,   112,   110,    60,    60,   255,    -1,    98,
     143,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    71
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     0,     1,     3,    25,    26,    32,    37,    51,    69,
      71,    72,    75,    77,   122,   123,   132,   145,   146,   147,
       0,    71,     1,    78,    70,   133,     0,    13,    81,     1,
      27,    23,    52,    53,   148,   149,    14,    19,    76,    69,
      62,   101,   104,     1,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    16,    17,    18,    20,    79,    82,    50,
      28,    49,    55,   150,    19,   134,   135,   136,   138,    14,
       1,    15,   105,   106,    23,    23,    97,   102,    23,    21,
      23,    19,    22,    22,    91,    85,    86,    87,    95,   124,
     125,    23,   153,    67,    63,    66,    38,    39,    41,    45,
     135,   137,    24,    33,   107,   108,    96,   102,   103,   107,
     109,   114,   115,   117,   118,   119,   120,    35,    35,    80,
      83,    84,    90,    22,    73,    19,    36,    92,    93,    94,
      19,    22,    23,    57,    58,    74,    31,     1,     4,     5,
      29,    79,   151,    56,   138,   139,   139,     1,    21,    23,
      36,    57,    58,    59,    98,   103,    35,    35,    62,   110,
     113,   103,   118,   103,   116,   117,   113,   109,   120,   121,
     102,   102,    88,    98,    19,    57,    58,    59,   100,    19,
      23,    74,    19,    23,    23,    23,   131,    23,    23,    23,
      54,   151,    40,    67,   144,    42,    61,    98,    98,    34,
      35,    61,    73,   103,   103,     1,   111,   113,   113,   113,
     120,    22,    89,    59,   100,    34,    35,    23,    23,     1,
      15,    50,   126,    22,   152,    67,    60,    98,    98,   110,
     112,    63,    23,    63,    99,    36,    99,    60,   100,   100,
      23,    30,   129,    19,    45,    46,    48,   140,   141,   143,
      99,    60,    73,   128,   130,    62,    43,   142,    60,    64,
      65,   127,    23,   143,    44,    47,    23,    63,    19,    48
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    68,    69,    70,    69,    69,    69,    69,    71,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    76,
      78,    77,    80,    79,    81,    81,    82,    82,    82,    82,
      83,    82,    84,    82,    82,    82,    82,    82,    85,    82,
      86,    82,    87,    82,    82,    82,    88,    88,    89,    90,
      90,    90,    90,    91,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    99,
     100,   100,   100,   100,   100,   100,   100,   101,   102,   103,
     104,   104,   105,   105,   105,   106,   107,   107,   107,   108,
     108,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   115,   116,   117,   117,   118,   119,
     119,   119,   120,   120,   121,   122,   122,   123,   123,   124,
     125,   125,   125,   125,   125,   125,   126,   127,   127,   128,
     128,   129,   130,   130,   131,   131,   131,   133,   132,   134,
     134,   134,   134,   135,   136,   136,   137,   137,   138,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     142,   143,   144,   144,   145,   145,   146,   147,   147,   148,
     149,   149,   150,   151,   151,   152,   153,   153
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     1,     2,     2,     1,     1,
       1,     1,     4,     3,     0,     1,     1,     1,     2,     1,
       0,     3,     0,     4,     0,     2,     2,     2,     2,     1,
       0,     4,     0,     4,     3,     3,     2,     2,     0,     3,
       0,     3,     0,     3,     2,     1,     0,     2,     1,     0,
       2,     2,     2,     0,     2,     3,     0,     3,     0,     3,
       0,     2,     0,     2,     2,     2,     2,     3,     3,     3,
       3,     1,     1,     1,     1,     2,     3,     3,     3,     1,
       4,     5,     3,     3,     3,     1,     1,     1,     1,     1,
       0,     2,     2,     2,     1,     5,     3,     1,     3,     0,
       1,     1,     3,     3,     0,     2,     0,     1,     0,     1,
       0,     1,     1,     2,     2,     2,     3,     3,     1,     1,
       2,     2,     2,     2,     2,     7,     3,     1,     1,     1,
       0,     2,     3,     3,     3,     2,     3,     1,     1,     0,
       3,     2,     0,     2,     0,     2,     4,     0,     5,     0,
       1,     3,     2,     2,     1,     2,     3,     3,     2,     1,
       2,     2,     0,     2,     1,     1,     1,     1,     0,     3,
       3,     2,     6,     3,     3,     2,     1,     2,     2,     1,
       0,     3,     3,     0,     2,     1,     0,     4
  };


#if HOAYYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"HOA:\"",
  "\"States:\"", "\"Start:\"", "\"AP:\"", "\"Alias:\"", "\"Acceptance:\"",
  "\"acc-name:\"", "\"tool:\"", "\"name:\"", "\"properties:\"",
  "\"--BODY--\"", "\"--END--\"", "\"State:\"", "\"spot.highlight.edges:\"",
  "\"spot.highlight.states:\"", "\"spot.state-player:\"", "\"identifier\"",
  "\"header name\"", "\"alias name\"", "\"string\"", "\"integer\"", "'['",
  "\"DRA\"", "\"DSA\"", "\"v2\"", "\"explicit\"", "\"Acceptance-Pairs:\"",
  "\"Acc-Sig:\"", "\"---\"", "\"#line\"", "BDD", "'|'", "'&'", "'!'",
  "\"never\"", "\"skip\"", "\"if\"", "\"fi\"", "\"do\"", "\"od\"",
  "\"->\"", "\"goto\"", "\"false\"", "\"atomic\"", "\"assert\"",
  "\"boolean formula\"", "\"-1\"", "\"end of DSTAR automaton\"",
  "\"LBTT header\"", "\"state acceptance\"",
  "\"acceptance sets for empty automaton\"", "\"acceptance set\"",
  "\"state number\"", "\"destination number\"", "'t'", "'f'", "'('", "')'",
  "']'", "'{'", "'}'", "'+'", "'-'", "';'", "':'", "$accept", "aut", "$@1",
  "aut-1", "hoa", "string_opt", "BOOLEAN", "header", "version",
  "format-version", "$@2", "aps", "$@3", "header-items", "header-item",
  "$@4", "$@5", "$@6", "$@7", "$@8", "ap-names", "ap-name", "acc-spec",
  "properties", "highlight-edges", "highlight-states", "state-player",
  "header-spec", "state-conj-2", "init-state-conj-2", "label-expr",
  "acc-set", "acceptance-cond", "body", "state-num", "checked-state-num",
  "states", "state", "state-name", "label", "state-label_opt",
  "trans-label", "acc-sig", "acc-sets", "state-acc_opt", "trans-acc_opt",
  "labeled-edges", "some-labeled-edges", "incorrectly-unlabeled-edge",
  "labeled-edge", "state-conj-checked", "unlabeled-edges",
  "unlabeled-edge", "incorrectly-labeled-edge", "dstar", "dstar_type",
  "dstar_header", "dstar_sizes", "dstar_state_id", "sign", "dstar_accsigs",
  "dstar_state_accsig", "dstar_transitions", "dstar_states", "never",
  "$@9", "nc-states", "nc-one-ident", "nc-ident-list",
  "nc-transition-block", "nc-state", "nc-transitions",
  "nc-formula-or-ident", "nc-formula", "nc-opt-dest", "nc-src-dest",
  "nc-transition", "lbtt", "lbtt-header-states", "lbtt-header",
  "lbtt-body", "lbtt-states", "lbtt-state", "lbtt-acc", "lbtt-guard",
  "lbtt-transitions", YY_NULLPTR
  };
#endif


#if HOAYYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   343,   343,   347,   347,   348,   349,   350,   357,   358,
     359,   360,   366,   367,   369,   370,   371,   371,   373,   677,
     684,   684,   687,   686,   739,   740,   741,   759,   764,   768,
     769,   769,   782,   781,   815,   819,   824,   828,   830,   829,
     833,   832,   836,   835,   844,   853,   855,   856,   857,   885,
     886,   887,   888,   892,   893,   914,   929,   930,   934,   935,
     940,   941,   948,   949,   950,   951,   955,   960,   964,   972,
     976,   982,   986,   990,  1019,  1034,  1040,  1047,  1054,  1060,
    1078,  1106,  1124,  1128,  1134,  1140,  1144,  1153,  1237,  1247,
    1290,  1291,  1330,  1331,  1355,  1365,  1395,  1403,  1404,  1410,
    1411,  1433,  1460,  1471,  1475,  1479,  1487,  1491,  1502,  1506,
    1520,  1521,  1522,  1523,  1524,  1525,  1543,  1554,  1567,  1582,
    1583,  1584,  1585,  1616,  1647,  1658,  1659,  1664,  1676,  1689,
    1713,  1714,  1715,  1733,  1746,  1750,  1752,  1792,  1793,  1796,
    1800,  1825,  1827,  1828,  1837,  1838,  1839,  1850,  1849,  1880,
    1881,  1882,  1883,  1885,  1896,  1906,  1924,  1928,  1934,  1944,
    1945,  1946,  1962,  1963,  1973,  1973,  1975,  2005,  2011,  2015,
    2019,  2026,  2045,  2049,  2058,  2099,  2105,  2118,  2123,  2128,
    2129,  2130,  2132,  2151,  2152,  2161,  2201,  2202
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
#endif // HOAYYDEBUG

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
       2,     2,     2,    36,     2,     2,     2,     2,    35,     2,
      59,    60,     2,    64,     2,    65,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    66,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,    58,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    57,     2,     2,     2,
       2,     2,     2,    62,    34,    63,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56
    };
    // Last valid token kind.
    const int code_max = 307;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // hoayy
#line 4070 "parseaut.cc"

#line 2221 "parseaut.yy"


static void fill_guards(result_& r)
{
  unsigned nap = r.ap.size();

  int* vars = new int[nap];
  for (unsigned i = 0; i < nap; ++i)
    vars[i] = r.ap[nap - 1 - i];

  // build the 2^nap possible guards
  r.guards.reserve(1U << nap);
  for (size_t i = 0; i < (1U << nap); ++i)
    r.guards.push_back(bdd_ibuildcube(i, nap, vars));
  r.cur_guard = r.guards.begin();

  delete[] vars;
}

void
hoayy::parser::error(const location_type& location,
		     const std::string& message)
{
  res.h->errors.emplace_back(location, message);
}

static spot::acc_cond::acc_code
fix_acceptance_aux(spot::acc_cond& acc,
		   spot::acc_cond::acc_code in, unsigned pos,
		   spot::acc_cond::mark_t onlyneg,
		   spot::acc_cond::mark_t both,
		   unsigned base)
{
  auto& w = in[pos];
  switch (w.sub.op)
    {
    case spot::acc_cond::acc_op::And:
      {
	unsigned sub = pos - w.sub.size;
	--pos;
	auto c = fix_acceptance_aux(acc, in, pos, onlyneg, both, base);
	pos -= in[pos].sub.size;
	while (sub < pos)
	  {
	    --pos;
	    c &= fix_acceptance_aux(acc, in, pos, onlyneg, both, base);
	    pos -= in[pos].sub.size;
	  }
	return c;
      }
    case spot::acc_cond::acc_op::Or:
      {
	unsigned sub = pos - w.sub.size;
	--pos;
	auto c = fix_acceptance_aux(acc, in, pos, onlyneg, both, base);
	pos -= in[pos].sub.size;
	while (sub < pos)
	  {
	    --pos;
	    c |= fix_acceptance_aux(acc, in, pos, onlyneg, both, base);
	    pos -= in[pos].sub.size;
	  }
	return c;
      }
    case spot::acc_cond::acc_op::Inf:
      return acc.inf(in[pos - 1].mark);
    case spot::acc_cond::acc_op::Fin:
      return acc.fin(in[pos - 1].mark);
    case spot::acc_cond::acc_op::FinNeg:
      {
	auto m = in[pos - 1].mark;
	auto c = acc.fin(onlyneg & m);
	spot::acc_cond::mark_t tmp = {};
	for (auto i: both.sets())
	  {
	    if (m.has(i))
	      tmp.set(base);
	    ++base;
	  }
	if (tmp)
	  c |= acc.fin(tmp);
	return c;
      }
    case spot::acc_cond::acc_op::InfNeg:
      {
	auto m = in[pos - 1].mark;
	auto c = acc.inf(onlyneg & m);
	spot::acc_cond::mark_t tmp = {};
	for (auto i: both.sets())
	  {
	    if (m.has(i))
	      tmp.set(base);
	    ++base;
	  }
	if (tmp)
	  c &= acc.inf(tmp);
	return c;
      }
    }
  SPOT_UNREACHABLE();
  return {};
}

static void fix_acceptance(result_& r)
{
  if (r.opts.want_kripke)
    return;
  auto& acc = r.h->aut->acc();

  // If a set x appears only as Inf(!x), we can complement it so that
  // we work with Inf(x) instead.
  auto onlyneg = r.neg_acc_sets - r.pos_acc_sets;
  if (onlyneg)
    {
      for (auto& t: r.h->aut->edge_vector())
	t.acc ^= onlyneg;
    }

  // However if set x is used elsewhere, for instance in
  //   Inf(!x) & Inf(x)
  // complementing x would be wrong.  We need to create a
  // new set, y, that is the complement of x, and rewrite
  // this as Inf(y) & Inf(x).
  auto both = r.neg_acc_sets & r.pos_acc_sets;
  unsigned base = 0;
  if (both)
    {
      base = acc.add_sets(both.count());
      for (auto& t: r.h->aut->edge_vector())
        {
          unsigned i = 0;
	  if ((t.acc & both) != both)
            for (unsigned v : both.sets())
              {
                if (!t.acc.has(v))
                  t.acc |= acc.mark(base + i);
                i++;
              }
        }
    }

  if (onlyneg || both)
    {
      auto& acc = r.h->aut->acc();
      auto code = acc.get_acceptance();
      r.h->aut->set_acceptance(acc.num_sets(),
			       fix_acceptance_aux(acc, code, code.size() - 1,
						  onlyneg, both, base));
    }
}

// Spot only supports a single initial state.
//
// If the input file does not declare any initial state (this is valid
// in the HOA format) add one nonetheless.
//
// If the input file has multiple initial states we have to merge
// them.
//
//   1) In the non-alternating case, this is as simple as making a new
//   initial state using the union of all the outgoing transitions of
//   the declared initial states.  Note that if one of the original
//   initial state has no incoming transition, then we can use it as
//   initial state, avoiding the creation of a new state.
//
//   2) In the alternating case, the input may have several initial
//   states that are conjuncts.  We have to reduce the conjuncts to a
//   single state first.

static void fix_initial_state(result_& r)
{
  std::vector<std::vector<unsigned>> start;
  start.reserve(r.start.size());
  unsigned ssz = r.info_states.size();
  for (auto& p : r.start)
    {
      std::vector<unsigned> v;
      v.reserve(p.second.size());
      for (unsigned s: p.second)
        // Ignore initial states without declaration
        // (They have been diagnosed already.)
        if (s < ssz && r.info_states[s].declared)
          v.emplace_back(s);
      if (!v.empty())
        start.push_back(v);
    }

  // If no initial state has been declared, add one.
  if (start.empty())
    {
      if (r.opts.want_kripke)
	r.h->ks->set_init_state(r.h->ks->new_state(bddfalse));
      else
	r.h->aut->set_init_state(r.h->aut->new_state());
      return;
    }

  // Remove any duplicate initial state.
  std::sort(start.begin(), start.end());
  auto res = std::unique(start.begin(), start.end());
  start.resize(std::distance(start.begin(), res));

  assert(start.size() >= 1);
  if (start.size() == 1)
    {
      if (r.opts.want_kripke)
	r.h->ks->set_init_state(start.front().front());
      else
	r.h->aut->set_univ_init_state(start.front().begin(),
                                      start.front().end());
    }
  else
    {
      if (r.opts.want_kripke)
	{
	  r.h->errors.emplace_front(r.start.front().first,
				    "Kripke structure only support "
				    "a single initial state");
	  return;
	}
      // Fiddling with initial state may turn an incomplete automaton
      // into a complete one.
      if (r.complete.is_false())
        r.complete = spot::trival::maybe();
      // Multiple initial states.  We might need to add a fake one,
      // unless one of the actual initial state has no incoming edge.
      auto& aut = r.h->aut;
      std::vector<unsigned char> has_incoming(aut->num_states(), 0);
      for (auto& t: aut->edges())
        for (unsigned ud: aut->univ_dests(t))
          has_incoming[ud] = 1;

      bool found = false;
      unsigned init = 0;
      bool init_alternation = false;
      for (auto& pp: start)
        if (pp.size() == 1)
          {
            unsigned p = pp.front();
            if (!has_incoming[p])
              {
                init = p;
                found = true;
              }
          }
        else
          {
            init_alternation = true;
            break;
          }

      if (!found || init_alternation)
	// We do need a fake initial state
	init = aut->new_state();
      aut->set_init_state(init);

      // The non-alternating case is the easiest, we simply declare
      // the outgoing transitions of all "original initial states"
      // into the only one initial state.
      if (!init_alternation)
        {
          for (auto& pp: start)
            {
              unsigned p = pp.front();
              if (p != init)
                for (auto& t: aut->out(p))
                  aut->new_edge(init, t.dst, t.cond);
            }
        }
      else
        {
          // In the alternating case, we merge outgoing transition of
          // the universal destination of conjunct initial states.
          // (Note that this loop would work for the non-alternating
          // case too, but it is more expansive, so we avoid it if we
          // can.)
          spot::outedge_combiner combiner(aut);
          bdd comb_or = bddfalse;
          for (auto& pp: start)
            {
              bdd comb_and = bddtrue;
              for (unsigned d: pp)
                comb_and &= combiner(d);
              comb_or |= comb_and;
            }
          combiner.new_dests(init, comb_or);
        }
    }
}

static void fix_properties(result_& r)
{
  r.aut_or_ks->prop_universal(r.universal);
  r.aut_or_ks->prop_complete(r.complete);
  if (r.acc_style == State_Acc ||
      (r.acc_style == Mixed_Acc && !r.trans_acc_seen))
    r.aut_or_ks->prop_state_acc(true);
}

static void check_version(const result_& r)
{
  if (r.h->type != spot::parsed_aut_type::HOA)
    return;
  auto& v = r.format_version;
  if (v.size() < 2 || v[0] != 'v' || v[1] < '1' || v[1] > '9')
    {
      r.h->errors.emplace_front(r.format_version_loc, "unknown HOA version");
      return;
    }
  const char* beg = &v[1];
  char* end = nullptr;
  long int vers = strtol(beg, &end, 10);
  if (vers != 1)
    {
      r.h->errors.emplace_front(r.format_version_loc,
				  "unsupported HOA version");
      return;
    }
  constexpr const char supported[] = "1";
  if (strverscmp(supported, beg) < 0 && !r.h->errors.empty())
    {
      std::ostringstream s;
      s << "we can read HOA v" << supported
	<< " but this file uses " << v << "; this might "
	"cause the following errors";
      r.h->errors.emplace_front(r.format_version_loc, s.str());
      return;
    }
}

namespace spot
{
  automaton_stream_parser::automaton_stream_parser(const std::string& name,
						   automaton_parser_options opt)
  try
    : filename_(name), opts_(opt)
  {
    if (hoayyopen(name, &scanner_))
      throw std::runtime_error("Cannot open file "s + name);
  }
  catch (...)
  {
    hoayyclose(scanner_);
    throw;
  }

  automaton_stream_parser::automaton_stream_parser(int fd,
						   const std::string& name,
						   automaton_parser_options opt)
  try
    : filename_(name), opts_(opt)
  {
    if (hoayyopen(fd, &scanner_))
      throw std::runtime_error("Cannot open file "s + name);
  }
  catch (...)
  {
    hoayyclose(scanner_);
    throw;
  }

  automaton_stream_parser::automaton_stream_parser(const char* data,
						   const std::string& filename,
						   automaton_parser_options opt)
  try
    : filename_(filename), opts_(opt)
  {
    hoayystring(data, &scanner_);
  }
  catch (...)
  {
    hoayyclose(scanner_);
    throw;
  }

  automaton_stream_parser::~automaton_stream_parser()
  {
    hoayyclose(scanner_);
  }

  static void raise_parse_error(const parsed_aut_ptr& pa)
  {
    if (pa->aborted)
      pa->errors.emplace_back(pa->loc, "parsing aborted");
    if (!pa->errors.empty())
      {
	std::ostringstream s;
	if (pa->format_errors(s))
	  throw parse_error(s.str());
      }
    // It is possible that pa->aut == nullptr if we reach the end of a
    // stream.  It is not necessarily an error.
  }

  parsed_aut_ptr
  automaton_stream_parser::parse(const bdd_dict_ptr& dict,
				 environment& env)
  {
  restart:
    result_ r;
    r.opts = opts_;
    r.h = std::make_shared<spot::parsed_aut>(filename_);
    if (opts_.want_kripke)
      r.aut_or_ks = r.h->ks = make_kripke_graph(dict);
    else
      r.aut_or_ks = r.h->aut = make_twa_graph(dict);
    r.env = &env;
    hoayy::parser parser(scanner_, r, last_loc);
    static bool env_debug = !!getenv("SPOT_DEBUG_PARSER");
    parser.set_debug_level(opts_.debug || env_debug);
    hoayyreset(scanner_);
    try
      {
	if (parser.parse())
	  {
	    r.h->aut = nullptr;
	    r.h->ks = nullptr;
	    r.aut_or_ks = nullptr;
	  }
      }
    catch (const spot::hoa_abort& e)
      {
	r.h->aborted = true;
	// Bison 3.0.2 lacks a += operator for locations.
	r.h->loc = r.h->loc + e.pos;
      }
    check_version(r);
    last_loc = r.h->loc;
    last_loc.step();
    filename_ = r.h->filename; // in case it was changed
    if (r.h->aborted)
      {
	if (opts_.ignore_abort)
	  goto restart;
	return r.h;
      }
    if (opts_.raise_errors)
      raise_parse_error(r.h);
    if (!r.aut_or_ks)
      return r.h;
    if (r.state_names)
      r.aut_or_ks->set_named_prop("state-names", r.state_names);
    if (r.highlight_edges)
      r.aut_or_ks->set_named_prop("highlight-edges", r.highlight_edges);
    if (r.highlight_states)
      r.aut_or_ks->set_named_prop("highlight-states", r.highlight_states);
    if (r.state_player)
      r.aut_or_ks->set_named_prop("state-player", r.state_player);
    fix_acceptance(r);
    fix_initial_state(r);
    fix_properties(r);
    if (r.h->aut && !r.h->aut->is_existential())
      r.h->aut->merge_univ_dests();
    return r.h;
  }

  parsed_aut_ptr
  parse_aut(const std::string& filename, const bdd_dict_ptr& dict,
	    environment& env, automaton_parser_options opts)
  {
    auto localopts = opts;
    localopts.raise_errors = false;
    parsed_aut_ptr pa;
    try
      {
	automaton_stream_parser p(filename, localopts);
	pa = p.parse(dict, env);
      }
    catch (const std::runtime_error& e)
      {
	if (opts.raise_errors)
	  throw;
	parsed_aut_ptr pa = std::make_shared<spot::parsed_aut>(filename);
	pa->errors.emplace_back(spot::location(), e.what());
	return pa;
      }
    if (!pa->aut && !pa->ks && pa->errors.empty())
      pa->errors.emplace_back(pa->loc, "no automaton read (empty input?)");
    if (opts.raise_errors)
      raise_parse_error(pa);
    return pa;
  }


}

// Local Variables:
// mode: c++
// End:
