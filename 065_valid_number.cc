/* Use finite automaton. The number consists of several fields: 
 *
 * Number text :    -28.82e-20   
 * Field number: 0001223445677888

 * field 0 is the blank character, can appear >=0 times, \s*
 * field 1 is either plus or minus sign, and can appear zero or one times, [\+\-]?
 * field 2 is the integer part, if exist, can have >=1 numbers, can also be absent if field 3 (dot) is present. \d+ | \.
 * field 3 is the dot, can appear once or be absent (pure integer) \.?
 * fields 2,3,4, we can only have 2, (e.g. 28), or 2-3 (28.0), or 2-3-4 (28.02), or 3-4 (.02), thus \d+ (\.\d*)? | \. \d+ (left of | is with 2, right of | is without 2)
 * field 4 is the fractional part, can be absent or contain multiple integers \d*
 * field 5 is the e/E character [eE]
 * field 6 is the sign, [\+\-]?
 * field 7 is the exponent, only integer is allowed, \d+.
 * fields 5,6,7 can be absent, thus ([eE][+-]?\d+)?
 * field 8 is the blank character, can appear >=0 times, \s*
 * Thus the regular expression for the valid number is:
 * \s*[\+\-]?(\d+(\.\d*)?|\.\d+)([eE][\+\-]?\d+)?\s*
 */
