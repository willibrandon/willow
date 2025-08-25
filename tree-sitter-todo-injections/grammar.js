module.exports = grammar({
  name: 'todo_injections',

  extras: $ => [
    /\s/,  // Allow whitespace
  ],

  rules: {
    source_file: $ => repeat($._item),

    _item: $ => choice(
      $.todo_item,
      $.fixme_item,
      $.hack_item,
      $.note_item,
      $.bug_item,
      $.optimize_item,
      $.deprecated_item,
      $.security_item,
      $.review_item,
      $.refactor_item,
    ),

    todo_item: $ => seq(
      field('keyword', /\b(TODO|todo|Todo)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    fixme_item: $ => seq(
      field('keyword', /\b(FIXME|fixme|FixMe)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    hack_item: $ => seq(
      field('keyword', /\b(HACK|hack|Hack)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    note_item: $ => seq(
      field('keyword', /\b(NOTE|note|Note)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    bug_item: $ => seq(
      field('keyword', /\b(BUG|bug|Bug)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    optimize_item: $ => seq(
      field('keyword', /\b(OPTIMIZE|OPTIMI[SZ]E|optimi[sz]e|Optimize)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    deprecated_item: $ => seq(
      field('keyword', /\b(DEPRECATED|deprecated|Deprecated)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    security_item: $ => seq(
      field('keyword', /\b(SECURITY|SEC|security|sec|Security)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    review_item: $ => seq(
      field('keyword', /\b(REVIEW|review|Review)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    refactor_item: $ => seq(
      field('keyword', /\b(REFACTOR|refactor|Refactor)\b/),
      optional(':'),
      optional(field('message', $.message))
    ),

    message: $ => /[^\r\n]*/,
  }
});