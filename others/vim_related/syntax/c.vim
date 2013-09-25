
syn match cFunction "/<[a-zA-Z_][a-zA-Z_0-9]*/>[^()]*)("me=e-2
syn match cFunction "/<[a-zA-Z_][a-zA-Z_0-9]*/>/s*("me=e-1

hi cFunction gui=NONE guifg=#B5A1FF

syn match cMathOperator display "[-+/*/%=]"

syn match cPointerOperator display "->/|/."

syn match cLogicalOperator display "[!<>]=/="

syn match cLogicalOperator display "=="

syn match cLogicalOperator display "/(&/||/|/^/|<</|>>/)=/="

syn match cBinaryOperator display "/~"

syn match cBinaryOperatorError display "/~="

syn match cLogicalOperator display "&&/|||"

syn match cLogicalOperator display "/(&&/|||/)="


hi cMathOperator guifg=#3EFFE2
hi cPointerOperator guifg=#3EFFE2
hi cLogicalOperator guifg=#3EFFE2
hi cBinaryOperator guifg=#3EFFE2
hi cBinaryOperatorError guifg=#3EFFE2
hi cLogicalOperator guifg=#3EFFE2
hi cLogicalOPeratorError guifg=#3EFFE2

