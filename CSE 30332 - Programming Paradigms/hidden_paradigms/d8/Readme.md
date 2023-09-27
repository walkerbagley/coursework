# Regular Expression Instructions

## Compilation

No compilation is required as this is a Python script


## Usage

`./matcher.py file.txt`


## Input Commands

1. `add` follows the form "add type argument"
    1. type can be one of `plus`, `star`, `dot`, `str`, `evil`, `open`, `close`
    2. if type is not one specified, the 
    2. `dot`, `open`, `close` do not take arguments
    3. The argument is the string to be passed in for `plus`, `star`, `str`, `evil`
    4. `evil` has a special argument `#` to denote applying the `evil` command to the current open group
    5. To apply `evil` to a sub-expression, a group must be opened with `add open` followed by everything contained in the group, and terminated with `add evil #` followed by `add close` which will add every possible string contained in the regex to the object
2. `match stringToBeMatched` will attempt to match `stringToBeMatched` to the current regular expression and output the result to the terminal


## Examples

### test.txt

Consider `test.txt` which tests every command except `evil` with the regular expression `cat.dog*` from the assignment:
```
add plus cat
add dot
add str d
add str o
add star g
```
Adding in a couple test cases:
```
match catcatQdogggggg
match turkeybaconcheese
```

Expected output for `./matcher.py test.txt`:
```
MATCH    - catcatQdogggggg
NO MATCH - turkeybaconcheese
```

### evil.txt

Consider `evil.txt` which builds the regular expression `acat((cat)εc(cat)εd)ε` from the assignment:
```
add str acat
add open
add evil cat
add str c
add evil cat
add str d
add evil #
add close
match acatcatccatcatdcatccatcatdcatccatcatd
match acatcatccatcatdcatccatcatd
```

Expected output for `./matcher.py evil.txt`:
```
MATCH    - acatcatccatcatdcatccatcatdcatccatcatd
NO MATCH - acatcatccatcatdcatccatcatd
```

## Notes

The matcher was taking far too long when adding in several star commands because of the high memory limit, so I ammended it to only consider possibilities where the substring from a command was less than or equal to the length of the string to be matched. Because I generate these possibilities upon calling `match`, the full regular expression is still intact and we can attempt matching much longer strings later if we'd like.