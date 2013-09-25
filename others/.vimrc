"auto save session
let g:AutoSessionFile="project.vim"
let g:OrigPWD=getcwd()
if filereadable(g:AutoSessionFile)
  if argc() == 0
	au VimEnter * call EnterHandler()
	au VimLeave * call LeaveHandler()
  endif
endif

function! LeaveHandler()
  exec "mks! ".g:OrigPWD."/".g:AutoSessionFile
endfunction


set history=700

set so=7
set wildmenu
set cmdheight=2

set nolazyredraw

set magic
set mat=2

set noerrorbells
set novisualbell

set ai
set si
set nowrap

set number
syntax enable
syntax on
set cindent

set tabstop=4
set shiftwidth=4
set expandtab
set showmatch

set incsearch

set encoding=utf8

set transparency=12
colorscheme torte 
set guifont=Monaco:h12
set fileencodings=ucs-bom,utf-8,utf-16,cp936,gb18030,big5,euc-jp,euc-kr,latin1

set tags=~/.vim/plugin/ctags-5.8
set completeopt=longest,menuone
let Tlist_Exit_OnlyWindow=1
let Tlist_Use_Right_Window=1
let Tlist_Show_One_File=0
let Tlist_Process_File_Always=1
let Tlist_Auto_Open=1

let g:winManagerWindowLayout='FileExplorer|TagList'
nmap wm:WMToggle<cr>
let g:miniBufExplMapWindowNavVim=1
let g:miniBufExplMapWindowNavArrows=1
filetype plugin indent on
set completeopt=mune
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

"
set cscopequickfix=s-,c-,d-,i-,t-,e-

cs add ~/.vim/cscope.out ~/.vim/

""""""""""""""""""""
" Bracket expanding
" """"""""""""""""""
vnoremap $1 <esc>`>a)<esc>`<i(<esc>
vnoremap $2 <esc>`>a]<esc>`<i[<esc>
vnoremap $3 <esc>`>a}<esc>`<i{<esc>
vnoremap $$ <esc>`>a"<esc>`<i"<esc>
vnoremap $q <esc>`>a'<esc>`<i'<esc>
vnoremap $e <esc>`>a"<esc>`<i"<esc>

" Map auto complete of (, ", ', [
inoremap $1 ()<esc>i
inoremap $2 []<esc>i
inoremap $3 {}<esc>i
inoremap $4 {<esc>o}<esc>O
inoremap $q ''<esc>i
inoremap $e ""<esc>i
inoremap $t <><esc>i

""""""""" minibuf"""""""""""

let g:miniBufExplModeSelTarget = 1
let g:bufExploreSortBy="name"

autocmd BufRead , BufNew:call UMiniBufExplorer

autocmd FileType css set omnifunc=csscomplete#CompleteCSS

map <leader>pp :setlocal spell!<cr>

"powerline{
"set guifont=PowerlineSymbols\ for\ Powerline
"set nocompatible
"set t_co = 256
"let g:Powerline_symbols='fancy'
"}
