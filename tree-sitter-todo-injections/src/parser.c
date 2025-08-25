#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 45
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 26
#define ALIAS_COUNT 0
#define TOKEN_COUNT 13
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 4

enum {
  aux_sym_todo_item_token1 = 1,
  anon_sym_COLON = 2,
  aux_sym_fixme_item_token1 = 3,
  aux_sym_hack_item_token1 = 4,
  aux_sym_note_item_token1 = 5,
  aux_sym_bug_item_token1 = 6,
  aux_sym_optimize_item_token1 = 7,
  aux_sym_deprecated_item_token1 = 8,
  aux_sym_security_item_token1 = 9,
  aux_sym_review_item_token1 = 10,
  aux_sym_refactor_item_token1 = 11,
  sym_message = 12,
  sym_source_file = 13,
  sym__item = 14,
  sym_todo_item = 15,
  sym_fixme_item = 16,
  sym_hack_item = 17,
  sym_note_item = 18,
  sym_bug_item = 19,
  sym_optimize_item = 20,
  sym_deprecated_item = 21,
  sym_security_item = 22,
  sym_review_item = 23,
  sym_refactor_item = 24,
  aux_sym_source_file_repeat1 = 25,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [aux_sym_todo_item_token1] = "todo_item_token1",
  [anon_sym_COLON] = ":",
  [aux_sym_fixme_item_token1] = "fixme_item_token1",
  [aux_sym_hack_item_token1] = "hack_item_token1",
  [aux_sym_note_item_token1] = "note_item_token1",
  [aux_sym_bug_item_token1] = "bug_item_token1",
  [aux_sym_optimize_item_token1] = "optimize_item_token1",
  [aux_sym_deprecated_item_token1] = "deprecated_item_token1",
  [aux_sym_security_item_token1] = "security_item_token1",
  [aux_sym_review_item_token1] = "review_item_token1",
  [aux_sym_refactor_item_token1] = "refactor_item_token1",
  [sym_message] = "message",
  [sym_source_file] = "source_file",
  [sym__item] = "_item",
  [sym_todo_item] = "todo_item",
  [sym_fixme_item] = "fixme_item",
  [sym_hack_item] = "hack_item",
  [sym_note_item] = "note_item",
  [sym_bug_item] = "bug_item",
  [sym_optimize_item] = "optimize_item",
  [sym_deprecated_item] = "deprecated_item",
  [sym_security_item] = "security_item",
  [sym_review_item] = "review_item",
  [sym_refactor_item] = "refactor_item",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [aux_sym_todo_item_token1] = aux_sym_todo_item_token1,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym_fixme_item_token1] = aux_sym_fixme_item_token1,
  [aux_sym_hack_item_token1] = aux_sym_hack_item_token1,
  [aux_sym_note_item_token1] = aux_sym_note_item_token1,
  [aux_sym_bug_item_token1] = aux_sym_bug_item_token1,
  [aux_sym_optimize_item_token1] = aux_sym_optimize_item_token1,
  [aux_sym_deprecated_item_token1] = aux_sym_deprecated_item_token1,
  [aux_sym_security_item_token1] = aux_sym_security_item_token1,
  [aux_sym_review_item_token1] = aux_sym_review_item_token1,
  [aux_sym_refactor_item_token1] = aux_sym_refactor_item_token1,
  [sym_message] = sym_message,
  [sym_source_file] = sym_source_file,
  [sym__item] = sym__item,
  [sym_todo_item] = sym_todo_item,
  [sym_fixme_item] = sym_fixme_item,
  [sym_hack_item] = sym_hack_item,
  [sym_note_item] = sym_note_item,
  [sym_bug_item] = sym_bug_item,
  [sym_optimize_item] = sym_optimize_item,
  [sym_deprecated_item] = sym_deprecated_item,
  [sym_security_item] = sym_security_item,
  [sym_review_item] = sym_review_item,
  [sym_refactor_item] = sym_refactor_item,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_todo_item_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_fixme_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_hack_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_note_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_bug_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_optimize_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_deprecated_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_security_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_review_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_refactor_item_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_message] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__item] = {
    .visible = false,
    .named = true,
  },
  [sym_todo_item] = {
    .visible = true,
    .named = true,
  },
  [sym_fixme_item] = {
    .visible = true,
    .named = true,
  },
  [sym_hack_item] = {
    .visible = true,
    .named = true,
  },
  [sym_note_item] = {
    .visible = true,
    .named = true,
  },
  [sym_bug_item] = {
    .visible = true,
    .named = true,
  },
  [sym_optimize_item] = {
    .visible = true,
    .named = true,
  },
  [sym_deprecated_item] = {
    .visible = true,
    .named = true,
  },
  [sym_security_item] = {
    .visible = true,
    .named = true,
  },
  [sym_review_item] = {
    .visible = true,
    .named = true,
  },
  [sym_refactor_item] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_keyword = 1,
  field_message = 2,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_keyword] = "keyword",
  [field_message] = "message",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_keyword, 0},
  [1] =
    {field_keyword, 0},
    {field_message, 1},
  [3] =
    {field_keyword, 0},
    {field_message, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ACCEPT_TOKEN(sym_message);
      if (eof) ADVANCE(105);
      if (lookahead == ':') ADVANCE(108);
      if (lookahead == 'B') ADVANCE(177);
      if (lookahead == 'D') ADVANCE(142);
      if (lookahead == 'F') ADVANCE(153);
      if (lookahead == 'H') ADVANCE(132);
      if (lookahead == 'N') ADVANCE(162);
      if (lookahead == 'O') ADVANCE(167);
      if (lookahead == 'R') ADVANCE(143);
      if (lookahead == 'S') ADVANCE(148);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == 'b') ADVANCE(228);
      if (lookahead == 'd') ADVANCE(196);
      if (lookahead == 'f') ADVANCE(204);
      if (lookahead == 'h') ADVANCE(181);
      if (lookahead == 'n') ADVANCE(213);
      if (lookahead == 'o') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(191);
      if (lookahead == 's') ADVANCE(198);
      if (lookahead == 't') ADVANCE(214);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(131);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 1:
      if (lookahead == 'A') ADVANCE(4);
      if (lookahead == 'a') ADVANCE(52);
      END_STATE();
    case 2:
      if (lookahead == 'A') ADVANCE(7);
      END_STATE();
    case 3:
      if (lookahead == 'A') ADVANCE(44);
      END_STATE();
    case 4:
      if (lookahead == 'C') ADVANCE(26);
      END_STATE();
    case 5:
      if (lookahead == 'C') ADVANCE(123);
      END_STATE();
    case 6:
      if (lookahead == 'C') ADVANCE(3);
      END_STATE();
    case 7:
      if (lookahead == 'C') ADVANCE(43);
      END_STATE();
    case 8:
      if (lookahead == 'D') ADVANCE(32);
      END_STATE();
    case 9:
      if (lookahead == 'D') ADVANCE(119);
      END_STATE();
    case 10:
      if (lookahead == 'E') ADVANCE(34);
      if (lookahead == 'e') ADVANCE(85);
      END_STATE();
    case 11:
      if (lookahead == 'E') ADVANCE(19);
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 12:
      if (lookahead == 'E') ADVANCE(113);
      END_STATE();
    case 13:
      if (lookahead == 'E') ADVANCE(109);
      END_STATE();
    case 14:
      if (lookahead == 'E') ADVANCE(46);
      END_STATE();
    case 15:
      if (lookahead == 'E') ADVANCE(117);
      END_STATE();
    case 16:
      if (lookahead == 'E') ADVANCE(5);
      if (lookahead == 'e') ADVANCE(54);
      END_STATE();
    case 17:
      if (lookahead == 'E') ADVANCE(9);
      END_STATE();
    case 18:
      if (lookahead == 'E') ADVANCE(6);
      END_STATE();
    case 19:
      if (lookahead == 'F') ADVANCE(2);
      if (lookahead == 'V') ADVANCE(25);
      END_STATE();
    case 20:
      if (lookahead == 'G') ADVANCE(115);
      END_STATE();
    case 21:
      if (lookahead == 'I') ADVANCE(47);
      if (lookahead == 'i') ADVANCE(100);
      END_STATE();
    case 22:
      if (lookahead == 'I') ADVANCE(39);
      END_STATE();
    case 23:
      if (lookahead == 'I') ADVANCE(28);
      END_STATE();
    case 24:
      if (lookahead == 'I') ADVANCE(42);
      END_STATE();
    case 25:
      if (lookahead == 'I') ADVANCE(14);
      END_STATE();
    case 26:
      if (lookahead == 'K') ADVANCE(111);
      END_STATE();
    case 27:
      if (lookahead == 'M') ADVANCE(13);
      END_STATE();
    case 28:
      if (lookahead == 'M') ADVANCE(22);
      END_STATE();
    case 29:
      if (lookahead == 'M') ADVANCE(61);
      END_STATE();
    case 30:
      if (lookahead == 'O') ADVANCE(40);
      if (lookahead == 'o') ADVANCE(92);
      END_STATE();
    case 31:
      if (lookahead == 'O') ADVANCE(8);
      if (lookahead == 'o') ADVANCE(58);
      END_STATE();
    case 32:
      if (lookahead == 'O') ADVANCE(106);
      END_STATE();
    case 33:
      if (lookahead == 'O') ADVANCE(36);
      END_STATE();
    case 34:
      if (lookahead == 'P') ADVANCE(37);
      END_STATE();
    case 35:
      if (lookahead == 'P') ADVANCE(41);
      if (lookahead == 'p') ADVANCE(91);
      END_STATE();
    case 36:
      if (lookahead == 'R') ADVANCE(129);
      END_STATE();
    case 37:
      if (lookahead == 'R') ADVANCE(18);
      END_STATE();
    case 38:
      if (lookahead == 'R') ADVANCE(24);
      END_STATE();
    case 39:
      if (lookahead == 'S') ADVANCE(15);
      if (lookahead == 'Z') ADVANCE(15);
      END_STATE();
    case 40:
      if (lookahead == 'T') ADVANCE(12);
      END_STATE();
    case 41:
      if (lookahead == 'T') ADVANCE(23);
      END_STATE();
    case 42:
      if (lookahead == 'T') ADVANCE(48);
      END_STATE();
    case 43:
      if (lookahead == 'T') ADVANCE(33);
      END_STATE();
    case 44:
      if (lookahead == 'T') ADVANCE(17);
      END_STATE();
    case 45:
      if (lookahead == 'U') ADVANCE(20);
      if (lookahead == 'u') ADVANCE(69);
      END_STATE();
    case 46:
      if (lookahead == 'W') ADVANCE(127);
      END_STATE();
    case 47:
      if (lookahead == 'X') ADVANCE(27);
      END_STATE();
    case 48:
      if (lookahead == 'Y') ADVANCE(121);
      END_STATE();
    case 49:
      if (lookahead == 'a') ADVANCE(52);
      END_STATE();
    case 50:
      if (lookahead == 'a') ADVANCE(56);
      END_STATE();
    case 51:
      if (lookahead == 'a') ADVANCE(94);
      END_STATE();
    case 52:
      if (lookahead == 'c') ADVANCE(77);
      END_STATE();
    case 53:
      if (lookahead == 'c') ADVANCE(125);
      END_STATE();
    case 54:
      if (lookahead == 'c') ADVANCE(97);
      END_STATE();
    case 55:
      if (lookahead == 'c') ADVANCE(51);
      END_STATE();
    case 56:
      if (lookahead == 'c') ADVANCE(93);
      END_STATE();
    case 57:
      if (lookahead == 'd') ADVANCE(119);
      END_STATE();
    case 58:
      if (lookahead == 'd') ADVANCE(83);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(113);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(109);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(98);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(117);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(85);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(57);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(53);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(55);
      END_STATE();
    case 68:
      if (lookahead == 'f') ADVANCE(50);
      if (lookahead == 'v') ADVANCE(75);
      END_STATE();
    case 69:
      if (lookahead == 'g') ADVANCE(115);
      END_STATE();
    case 70:
      if (lookahead == 'i') ADVANCE(102);
      END_STATE();
    case 71:
      if (lookahead == 'i') ADVANCE(103);
      END_STATE();
    case 72:
      if (lookahead == 'i') ADVANCE(99);
      END_STATE();
    case 73:
      if (lookahead == 'i') ADVANCE(78);
      END_STATE();
    case 74:
      if (lookahead == 'i') ADVANCE(90);
      END_STATE();
    case 75:
      if (lookahead == 'i') ADVANCE(62);
      END_STATE();
    case 76:
      if (lookahead == 'i') ADVANCE(80);
      END_STATE();
    case 77:
      if (lookahead == 'k') ADVANCE(111);
      END_STATE();
    case 78:
      if (lookahead == 'm') ADVANCE(70);
      END_STATE();
    case 79:
      if (lookahead == 'm') ADVANCE(61);
      END_STATE();
    case 80:
      if (lookahead == 'm') ADVANCE(71);
      END_STATE();
    case 81:
      if (lookahead == 'o') ADVANCE(92);
      END_STATE();
    case 82:
      if (lookahead == 'o') ADVANCE(58);
      END_STATE();
    case 83:
      if (lookahead == 'o') ADVANCE(106);
      END_STATE();
    case 84:
      if (lookahead == 'o') ADVANCE(87);
      END_STATE();
    case 85:
      if (lookahead == 'p') ADVANCE(89);
      END_STATE();
    case 86:
      if (lookahead == 'p') ADVANCE(95);
      END_STATE();
    case 87:
      if (lookahead == 'r') ADVANCE(129);
      END_STATE();
    case 88:
      if (lookahead == 'r') ADVANCE(74);
      END_STATE();
    case 89:
      if (lookahead == 'r') ADVANCE(67);
      END_STATE();
    case 90:
      if (lookahead == 't') ADVANCE(101);
      END_STATE();
    case 91:
      if (lookahead == 't') ADVANCE(73);
      END_STATE();
    case 92:
      if (lookahead == 't') ADVANCE(60);
      END_STATE();
    case 93:
      if (lookahead == 't') ADVANCE(84);
      END_STATE();
    case 94:
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 95:
      if (lookahead == 't') ADVANCE(76);
      END_STATE();
    case 96:
      if (lookahead == 'u') ADVANCE(69);
      END_STATE();
    case 97:
      if (lookahead == 'u') ADVANCE(88);
      END_STATE();
    case 98:
      if (lookahead == 'w') ADVANCE(127);
      END_STATE();
    case 99:
      if (lookahead == 'x') ADVANCE(79);
      END_STATE();
    case 100:
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 101:
      if (lookahead == 'y') ADVANCE(121);
      END_STATE();
    case 102:
      if (lookahead == 'z') ADVANCE(63);
      END_STATE();
    case 103:
      if (lookahead == 's' ||
          lookahead == 'z') ADVANCE(63);
      END_STATE();
    case 104:
      if (eof) ADVANCE(105);
      if (lookahead == 'B') ADVANCE(45);
      if (lookahead == 'D') ADVANCE(10);
      if (lookahead == 'F') ADVANCE(21);
      if (lookahead == 'H') ADVANCE(1);
      if (lookahead == 'N') ADVANCE(30);
      if (lookahead == 'O') ADVANCE(35);
      if (lookahead == 'R') ADVANCE(11);
      if (lookahead == 'S') ADVANCE(16);
      if (lookahead == 'T') ADVANCE(31);
      if (lookahead == 'b') ADVANCE(96);
      if (lookahead == 'd') ADVANCE(64);
      if (lookahead == 'f') ADVANCE(72);
      if (lookahead == 'h') ADVANCE(49);
      if (lookahead == 'n') ADVANCE(81);
      if (lookahead == 'o') ADVANCE(86);
      if (lookahead == 'r') ADVANCE(59);
      if (lookahead == 's') ADVANCE(66);
      if (lookahead == 't') ADVANCE(82);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(104)
      END_STATE();
    case 105:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(aux_sym_todo_item_token1);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(aux_sym_todo_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(aux_sym_fixme_item_token1);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(aux_sym_fixme_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(aux_sym_hack_item_token1);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(aux_sym_hack_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(aux_sym_note_item_token1);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(aux_sym_note_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_bug_item_token1);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym_bug_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(aux_sym_optimize_item_token1);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(aux_sym_optimize_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(aux_sym_deprecated_item_token1);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(aux_sym_deprecated_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      if (lookahead == 'U') ADVANCE(170);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      if (lookahead == 'U') ADVANCE(38);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      if (lookahead == 'u') ADVANCE(220);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      if (lookahead == 'u') ADVANCE(88);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(aux_sym_security_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(aux_sym_review_item_token1);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(aux_sym_review_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(aux_sym_refactor_item_token1);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(aux_sym_refactor_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == ':') ADVANCE(108);
      if (lookahead == 'B') ADVANCE(177);
      if (lookahead == 'D') ADVANCE(142);
      if (lookahead == 'F') ADVANCE(153);
      if (lookahead == 'H') ADVANCE(132);
      if (lookahead == 'N') ADVANCE(162);
      if (lookahead == 'O') ADVANCE(167);
      if (lookahead == 'R') ADVANCE(143);
      if (lookahead == 'S') ADVANCE(148);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == 'b') ADVANCE(228);
      if (lookahead == 'd') ADVANCE(196);
      if (lookahead == 'f') ADVANCE(204);
      if (lookahead == 'h') ADVANCE(181);
      if (lookahead == 'n') ADVANCE(213);
      if (lookahead == 'o') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(191);
      if (lookahead == 's') ADVANCE(198);
      if (lookahead == 't') ADVANCE(214);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(131);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'A') ADVANCE(136);
      if (lookahead == 'a') ADVANCE(184);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'A') ADVANCE(139);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'A') ADVANCE(176);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'B') ADVANCE(177);
      if (lookahead == 'D') ADVANCE(142);
      if (lookahead == 'F') ADVANCE(153);
      if (lookahead == 'H') ADVANCE(132);
      if (lookahead == 'N') ADVANCE(162);
      if (lookahead == 'O') ADVANCE(167);
      if (lookahead == 'R') ADVANCE(143);
      if (lookahead == 'S') ADVANCE(148);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == 'b') ADVANCE(228);
      if (lookahead == 'd') ADVANCE(196);
      if (lookahead == 'f') ADVANCE(204);
      if (lookahead == 'h') ADVANCE(181);
      if (lookahead == 'n') ADVANCE(213);
      if (lookahead == 'o') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(191);
      if (lookahead == 's') ADVANCE(198);
      if (lookahead == 't') ADVANCE(214);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'C') ADVANCE(158);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'C') ADVANCE(122);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'C') ADVANCE(134);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'C') ADVANCE(175);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'D') ADVANCE(164);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'D') ADVANCE(120);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(166);
      if (lookahead == 'e') ADVANCE(217);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(151);
      if (lookahead == 'e') ADVANCE(200);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(114);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(110);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(178);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(118);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(137);
      if (lookahead == 'e') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(141);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'E') ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'F') ADVANCE(133);
      if (lookahead == 'V') ADVANCE(157);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'G') ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'I') ADVANCE(179);
      if (lookahead == 'i') ADVANCE(232);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'I') ADVANCE(171);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'I') ADVANCE(160);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'I') ADVANCE(174);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'I') ADVANCE(146);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'K') ADVANCE(112);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'M') ADVANCE(145);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'M') ADVANCE(154);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'M') ADVANCE(193);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'O') ADVANCE(172);
      if (lookahead == 'o') ADVANCE(224);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'O') ADVANCE(140);
      if (lookahead == 'o') ADVANCE(190);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'O') ADVANCE(107);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'O') ADVANCE(168);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'P') ADVANCE(169);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'P') ADVANCE(173);
      if (lookahead == 'p') ADVANCE(223);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'R') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'R') ADVANCE(150);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'R') ADVANCE(156);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'S') ADVANCE(147);
      if (lookahead == 'Z') ADVANCE(147);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'T') ADVANCE(144);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'T') ADVANCE(155);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'T') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'T') ADVANCE(165);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'T') ADVANCE(149);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'U') ADVANCE(152);
      if (lookahead == 'u') ADVANCE(201);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'W') ADVANCE(128);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'X') ADVANCE(159);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'Y') ADVANCE(126);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'a') ADVANCE(184);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'a') ADVANCE(188);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'a') ADVANCE(226);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'c') ADVANCE(209);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'c') ADVANCE(124);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'c') ADVANCE(229);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'c') ADVANCE(183);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'c') ADVANCE(225);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'd') ADVANCE(120);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'd') ADVANCE(215);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(200);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(114);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(110);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(230);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(118);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(217);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(189);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(185);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'e') ADVANCE(187);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'f') ADVANCE(182);
      if (lookahead == 'v') ADVANCE(207);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'g') ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(234);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(235);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(231);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(210);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(222);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(194);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'i') ADVANCE(212);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'k') ADVANCE(112);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'm') ADVANCE(202);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'm') ADVANCE(193);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'm') ADVANCE(203);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'o') ADVANCE(224);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'o') ADVANCE(190);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'o') ADVANCE(107);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'o') ADVANCE(219);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'p') ADVANCE(221);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'p') ADVANCE(227);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'r') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'r') ADVANCE(206);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'r') ADVANCE(199);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(233);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(205);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(192);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(216);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(197);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 't') ADVANCE(208);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'u') ADVANCE(201);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'u') ADVANCE(220);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'w') ADVANCE(128);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'x') ADVANCE(211);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'x') ADVANCE(161);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'y') ADVANCE(126);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 'z') ADVANCE(195);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_message);
      if (lookahead == 's' ||
          lookahead == 'z') ADVANCE(195);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_message);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_message);
      if (eof) ADVANCE(105);
      if (lookahead == 'B') ADVANCE(177);
      if (lookahead == 'D') ADVANCE(142);
      if (lookahead == 'F') ADVANCE(153);
      if (lookahead == 'H') ADVANCE(132);
      if (lookahead == 'N') ADVANCE(162);
      if (lookahead == 'O') ADVANCE(167);
      if (lookahead == 'R') ADVANCE(143);
      if (lookahead == 'S') ADVANCE(148);
      if (lookahead == 'T') ADVANCE(163);
      if (lookahead == 'b') ADVANCE(228);
      if (lookahead == 'd') ADVANCE(196);
      if (lookahead == 'f') ADVANCE(204);
      if (lookahead == 'h') ADVANCE(181);
      if (lookahead == 'n') ADVANCE(213);
      if (lookahead == 'o') ADVANCE(218);
      if (lookahead == 'r') ADVANCE(191);
      if (lookahead == 's') ADVANCE(198);
      if (lookahead == 't') ADVANCE(214);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(236);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 104},
  [2] = {.lex_state = 104},
  [3] = {.lex_state = 104},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 237},
  [15] = {.lex_state = 237},
  [16] = {.lex_state = 237},
  [17] = {.lex_state = 237},
  [18] = {.lex_state = 237},
  [19] = {.lex_state = 237},
  [20] = {.lex_state = 237},
  [21] = {.lex_state = 237},
  [22] = {.lex_state = 237},
  [23] = {.lex_state = 237},
  [24] = {.lex_state = 104},
  [25] = {.lex_state = 104},
  [26] = {.lex_state = 104},
  [27] = {.lex_state = 104},
  [28] = {.lex_state = 104},
  [29] = {.lex_state = 104},
  [30] = {.lex_state = 104},
  [31] = {.lex_state = 104},
  [32] = {.lex_state = 104},
  [33] = {.lex_state = 104},
  [34] = {.lex_state = 104},
  [35] = {.lex_state = 104},
  [36] = {.lex_state = 104},
  [37] = {.lex_state = 104},
  [38] = {.lex_state = 104},
  [39] = {.lex_state = 104},
  [40] = {.lex_state = 104},
  [41] = {.lex_state = 104},
  [42] = {.lex_state = 104},
  [43] = {.lex_state = 104},
  [44] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [aux_sym_todo_item_token1] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [aux_sym_fixme_item_token1] = ACTIONS(1),
    [aux_sym_hack_item_token1] = ACTIONS(1),
    [aux_sym_note_item_token1] = ACTIONS(1),
    [aux_sym_bug_item_token1] = ACTIONS(1),
    [aux_sym_optimize_item_token1] = ACTIONS(1),
    [aux_sym_deprecated_item_token1] = ACTIONS(1),
    [aux_sym_security_item_token1] = ACTIONS(1),
    [aux_sym_review_item_token1] = ACTIONS(1),
    [aux_sym_refactor_item_token1] = ACTIONS(1),
    [sym_message] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(44),
    [sym__item] = STATE(3),
    [sym_todo_item] = STATE(3),
    [sym_fixme_item] = STATE(3),
    [sym_hack_item] = STATE(3),
    [sym_note_item] = STATE(3),
    [sym_bug_item] = STATE(3),
    [sym_optimize_item] = STATE(3),
    [sym_deprecated_item] = STATE(3),
    [sym_security_item] = STATE(3),
    [sym_review_item] = STATE(3),
    [sym_refactor_item] = STATE(3),
    [aux_sym_source_file_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym_todo_item_token1] = ACTIONS(5),
    [aux_sym_fixme_item_token1] = ACTIONS(7),
    [aux_sym_hack_item_token1] = ACTIONS(9),
    [aux_sym_note_item_token1] = ACTIONS(11),
    [aux_sym_bug_item_token1] = ACTIONS(13),
    [aux_sym_optimize_item_token1] = ACTIONS(15),
    [aux_sym_deprecated_item_token1] = ACTIONS(17),
    [aux_sym_security_item_token1] = ACTIONS(19),
    [aux_sym_review_item_token1] = ACTIONS(21),
    [aux_sym_refactor_item_token1] = ACTIONS(23),
  },
  [2] = {
    [sym__item] = STATE(2),
    [sym_todo_item] = STATE(2),
    [sym_fixme_item] = STATE(2),
    [sym_hack_item] = STATE(2),
    [sym_note_item] = STATE(2),
    [sym_bug_item] = STATE(2),
    [sym_optimize_item] = STATE(2),
    [sym_deprecated_item] = STATE(2),
    [sym_security_item] = STATE(2),
    [sym_review_item] = STATE(2),
    [sym_refactor_item] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(25),
    [aux_sym_todo_item_token1] = ACTIONS(27),
    [aux_sym_fixme_item_token1] = ACTIONS(30),
    [aux_sym_hack_item_token1] = ACTIONS(33),
    [aux_sym_note_item_token1] = ACTIONS(36),
    [aux_sym_bug_item_token1] = ACTIONS(39),
    [aux_sym_optimize_item_token1] = ACTIONS(42),
    [aux_sym_deprecated_item_token1] = ACTIONS(45),
    [aux_sym_security_item_token1] = ACTIONS(48),
    [aux_sym_review_item_token1] = ACTIONS(51),
    [aux_sym_refactor_item_token1] = ACTIONS(54),
  },
  [3] = {
    [sym__item] = STATE(2),
    [sym_todo_item] = STATE(2),
    [sym_fixme_item] = STATE(2),
    [sym_hack_item] = STATE(2),
    [sym_note_item] = STATE(2),
    [sym_bug_item] = STATE(2),
    [sym_optimize_item] = STATE(2),
    [sym_deprecated_item] = STATE(2),
    [sym_security_item] = STATE(2),
    [sym_review_item] = STATE(2),
    [sym_refactor_item] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(57),
    [aux_sym_todo_item_token1] = ACTIONS(5),
    [aux_sym_fixme_item_token1] = ACTIONS(7),
    [aux_sym_hack_item_token1] = ACTIONS(9),
    [aux_sym_note_item_token1] = ACTIONS(11),
    [aux_sym_bug_item_token1] = ACTIONS(13),
    [aux_sym_optimize_item_token1] = ACTIONS(15),
    [aux_sym_deprecated_item_token1] = ACTIONS(17),
    [aux_sym_security_item_token1] = ACTIONS(19),
    [aux_sym_review_item_token1] = ACTIONS(21),
    [aux_sym_refactor_item_token1] = ACTIONS(23),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 4,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    ACTIONS(63), 1,
      anon_sym_COLON,
    ACTIONS(65), 1,
      sym_message,
    ACTIONS(61), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [22] = 4,
    ACTIONS(67), 1,
      ts_builtin_sym_end,
    ACTIONS(71), 1,
      anon_sym_COLON,
    ACTIONS(73), 1,
      sym_message,
    ACTIONS(69), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [44] = 4,
    ACTIONS(75), 1,
      ts_builtin_sym_end,
    ACTIONS(79), 1,
      anon_sym_COLON,
    ACTIONS(81), 1,
      sym_message,
    ACTIONS(77), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [66] = 4,
    ACTIONS(83), 1,
      ts_builtin_sym_end,
    ACTIONS(87), 1,
      anon_sym_COLON,
    ACTIONS(89), 1,
      sym_message,
    ACTIONS(85), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [88] = 4,
    ACTIONS(91), 1,
      ts_builtin_sym_end,
    ACTIONS(95), 1,
      anon_sym_COLON,
    ACTIONS(97), 1,
      sym_message,
    ACTIONS(93), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [110] = 4,
    ACTIONS(99), 1,
      ts_builtin_sym_end,
    ACTIONS(103), 1,
      anon_sym_COLON,
    ACTIONS(105), 1,
      sym_message,
    ACTIONS(101), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [132] = 4,
    ACTIONS(107), 1,
      ts_builtin_sym_end,
    ACTIONS(111), 1,
      anon_sym_COLON,
    ACTIONS(113), 1,
      sym_message,
    ACTIONS(109), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [154] = 4,
    ACTIONS(115), 1,
      ts_builtin_sym_end,
    ACTIONS(119), 1,
      anon_sym_COLON,
    ACTIONS(121), 1,
      sym_message,
    ACTIONS(117), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [176] = 4,
    ACTIONS(123), 1,
      ts_builtin_sym_end,
    ACTIONS(127), 1,
      anon_sym_COLON,
    ACTIONS(129), 1,
      sym_message,
    ACTIONS(125), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [198] = 4,
    ACTIONS(131), 1,
      ts_builtin_sym_end,
    ACTIONS(135), 1,
      anon_sym_COLON,
    ACTIONS(137), 1,
      sym_message,
    ACTIONS(133), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [220] = 3,
    ACTIONS(139), 1,
      ts_builtin_sym_end,
    ACTIONS(143), 1,
      sym_message,
    ACTIONS(141), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [239] = 3,
    ACTIONS(145), 1,
      ts_builtin_sym_end,
    ACTIONS(149), 1,
      sym_message,
    ACTIONS(147), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [258] = 3,
    ACTIONS(151), 1,
      ts_builtin_sym_end,
    ACTIONS(155), 1,
      sym_message,
    ACTIONS(153), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [277] = 3,
    ACTIONS(157), 1,
      ts_builtin_sym_end,
    ACTIONS(161), 1,
      sym_message,
    ACTIONS(159), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [296] = 3,
    ACTIONS(163), 1,
      ts_builtin_sym_end,
    ACTIONS(167), 1,
      sym_message,
    ACTIONS(165), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [315] = 3,
    ACTIONS(169), 1,
      ts_builtin_sym_end,
    ACTIONS(173), 1,
      sym_message,
    ACTIONS(171), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [334] = 3,
    ACTIONS(175), 1,
      ts_builtin_sym_end,
    ACTIONS(179), 1,
      sym_message,
    ACTIONS(177), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [353] = 3,
    ACTIONS(181), 1,
      ts_builtin_sym_end,
    ACTIONS(185), 1,
      sym_message,
    ACTIONS(183), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [372] = 3,
    ACTIONS(187), 1,
      ts_builtin_sym_end,
    ACTIONS(191), 1,
      sym_message,
    ACTIONS(189), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [391] = 3,
    ACTIONS(193), 1,
      ts_builtin_sym_end,
    ACTIONS(197), 1,
      sym_message,
    ACTIONS(195), 10,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [410] = 1,
    ACTIONS(199), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [424] = 1,
    ACTIONS(201), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [438] = 1,
    ACTIONS(203), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [452] = 1,
    ACTIONS(205), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [466] = 1,
    ACTIONS(207), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [480] = 1,
    ACTIONS(209), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [494] = 1,
    ACTIONS(211), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [508] = 1,
    ACTIONS(213), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [522] = 1,
    ACTIONS(215), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [536] = 1,
    ACTIONS(217), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [550] = 1,
    ACTIONS(219), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [564] = 1,
    ACTIONS(221), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [578] = 1,
    ACTIONS(223), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [592] = 1,
    ACTIONS(225), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [606] = 1,
    ACTIONS(227), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [620] = 1,
    ACTIONS(229), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [634] = 1,
    ACTIONS(231), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [648] = 1,
    ACTIONS(233), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [662] = 1,
    ACTIONS(235), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [676] = 1,
    ACTIONS(237), 11,
      ts_builtin_sym_end,
      aux_sym_todo_item_token1,
      aux_sym_fixme_item_token1,
      aux_sym_hack_item_token1,
      aux_sym_note_item_token1,
      aux_sym_bug_item_token1,
      aux_sym_optimize_item_token1,
      aux_sym_deprecated_item_token1,
      aux_sym_security_item_token1,
      aux_sym_review_item_token1,
      aux_sym_refactor_item_token1,
  [690] = 1,
    ACTIONS(239), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 22,
  [SMALL_STATE(6)] = 44,
  [SMALL_STATE(7)] = 66,
  [SMALL_STATE(8)] = 88,
  [SMALL_STATE(9)] = 110,
  [SMALL_STATE(10)] = 132,
  [SMALL_STATE(11)] = 154,
  [SMALL_STATE(12)] = 176,
  [SMALL_STATE(13)] = 198,
  [SMALL_STATE(14)] = 220,
  [SMALL_STATE(15)] = 239,
  [SMALL_STATE(16)] = 258,
  [SMALL_STATE(17)] = 277,
  [SMALL_STATE(18)] = 296,
  [SMALL_STATE(19)] = 315,
  [SMALL_STATE(20)] = 334,
  [SMALL_STATE(21)] = 353,
  [SMALL_STATE(22)] = 372,
  [SMALL_STATE(23)] = 391,
  [SMALL_STATE(24)] = 410,
  [SMALL_STATE(25)] = 424,
  [SMALL_STATE(26)] = 438,
  [SMALL_STATE(27)] = 452,
  [SMALL_STATE(28)] = 466,
  [SMALL_STATE(29)] = 480,
  [SMALL_STATE(30)] = 494,
  [SMALL_STATE(31)] = 508,
  [SMALL_STATE(32)] = 522,
  [SMALL_STATE(33)] = 536,
  [SMALL_STATE(34)] = 550,
  [SMALL_STATE(35)] = 564,
  [SMALL_STATE(36)] = 578,
  [SMALL_STATE(37)] = 592,
  [SMALL_STATE(38)] = 606,
  [SMALL_STATE(39)] = 620,
  [SMALL_STATE(40)] = 634,
  [SMALL_STATE(41)] = 648,
  [SMALL_STATE(42)] = 662,
  [SMALL_STATE(43)] = 676,
  [SMALL_STATE(44)] = 690,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(4),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(5),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(6),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(7),
  [39] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(8),
  [42] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(9),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(10),
  [48] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(11),
  [51] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(12),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(13),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_item, 1, .production_id = 1),
  [61] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_item, 1, .production_id = 1),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fixme_item, 1, .production_id = 1),
  [69] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fixme_item, 1, .production_id = 1),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [73] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hack_item, 1, .production_id = 1),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hack_item, 1, .production_id = 1),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [81] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_item, 1, .production_id = 1),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_note_item, 1, .production_id = 1),
  [87] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [89] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bug_item, 1, .production_id = 1),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bug_item, 1, .production_id = 1),
  [95] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [97] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_optimize_item, 1, .production_id = 1),
  [101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_optimize_item, 1, .production_id = 1),
  [103] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [105] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_item, 1, .production_id = 1),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deprecated_item, 1, .production_id = 1),
  [111] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_security_item, 1, .production_id = 1),
  [117] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_security_item, 1, .production_id = 1),
  [119] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_review_item, 1, .production_id = 1),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_review_item, 1, .production_id = 1),
  [127] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_refactor_item, 1, .production_id = 1),
  [133] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_refactor_item, 1, .production_id = 1),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [137] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bug_item, 2, .production_id = 1),
  [141] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bug_item, 2, .production_id = 1),
  [143] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_optimize_item, 2, .production_id = 1),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_optimize_item, 2, .production_id = 1),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_refactor_item, 2, .production_id = 1),
  [153] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_refactor_item, 2, .production_id = 1),
  [155] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fixme_item, 2, .production_id = 1),
  [159] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fixme_item, 2, .production_id = 1),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_review_item, 2, .production_id = 1),
  [165] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_review_item, 2, .production_id = 1),
  [167] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hack_item, 2, .production_id = 1),
  [171] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_hack_item, 2, .production_id = 1),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_item, 2, .production_id = 1),
  [177] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_todo_item, 2, .production_id = 1),
  [179] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_item, 2, .production_id = 1),
  [183] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_note_item, 2, .production_id = 1),
  [185] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_security_item, 2, .production_id = 1),
  [189] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_security_item, 2, .production_id = 1),
  [191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_item, 2, .production_id = 1),
  [195] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deprecated_item, 2, .production_id = 1),
  [197] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_security_item, 2, .production_id = 2),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_optimize_item, 2, .production_id = 2),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_item, 2, .production_id = 2),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_item, 2, .production_id = 2),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bug_item, 2, .production_id = 2),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_item, 2, .production_id = 2),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hack_item, 2, .production_id = 2),
  [213] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_review_item, 2, .production_id = 2),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fixme_item, 2, .production_id = 2),
  [217] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_refactor_item, 2, .production_id = 2),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_todo_item, 3, .production_id = 3),
  [221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fixme_item, 3, .production_id = 3),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hack_item, 3, .production_id = 3),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note_item, 3, .production_id = 3),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bug_item, 3, .production_id = 3),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_optimize_item, 3, .production_id = 3),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_item, 3, .production_id = 3),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_security_item, 3, .production_id = 3),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_review_item, 3, .production_id = 3),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_refactor_item, 3, .production_id = 3),
  [239] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_todo_injections(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
