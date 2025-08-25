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
      field('keyword', /(TODO|todo|Todo)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    fixme_item: $ => seq(
      field('keyword', /(FIXME|fixme|FixMe)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    hack_item: $ => seq(
      field('keyword', /(HACK|hack|Hack)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    note_item: $ => seq(
      field('keyword', /(NOTE|note|Note)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    bug_item: $ => seq(
      field('keyword', /(BUG|bug|Bug)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    optimize_item: $ => seq(
      field('keyword', /(OPTIMIZE|OPTIMI[SZ]E|optimi[sz]e|Optimize)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    deprecated_item: $ => seq(
      field('keyword', /(DEPRECATED|deprecated|Deprecated)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    security_item: $ => seq(
      field('keyword', /(SECURITY|SEC|security|sec|Security)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    review_item: $ => seq(
      field('keyword', /(REVIEW|review|Review)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    refactor_item: $ => seq(
      field('keyword', /(REFACTOR|refactor|Refactor)/),
      optional(':'),
      optional(field('message', $.message))
    ),

    message: $ => /[^\r\n]*/,
  }
});