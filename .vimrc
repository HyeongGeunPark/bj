" Vim with all enhancements
source $VIMRUNTIME/vimrc_example.vim

" Use the internal diff if available.
" Otherwise use the special 'diffexpr' for Windows.
if &diffopt !~# 'internal'
  set diffexpr=MyDiff()
endif
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg1 = substitute(arg1, '!', '\!', 'g')
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg2 = substitute(arg2, '!', '\!', 'g')
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let arg3 = substitute(arg3, '!', '\!', 'g')
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      if empty(&shellxquote)
        let l:shxq_sav = ''
        set shellxquote&
      endif
      let cmd = '"' . $VIMRUNTIME . '\diff"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  let cmd = substitute(cmd, '!', '\!', 'g')
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3
  if exists('l:shxq_sav')
    let &shellxquote=l:shxq_sav
  endif
endfunction

if has("syntax")
	syntax on
endif

"set hlsearch "검색어 하이라이팅
set nu "줄번호
set autoindent "자동 들여쓰기
set scrolloff=2
set wildmode=longest,list
set ts=4 "tab 크기 
set sts=4 "st select
set sw=1 " 스크롤바 너비
set autowrite " 다른 파일로 넘어갈 때 자동 저장
set autoread " 작업 중인 파일 외부에서 변경됬을 경우 자동으로 불러옴
set cindent " C언어 자동 들여쓰기
set bs=eol,start,indent
set history=256
set laststatus=2 " 상태바 표시 항상
"set paste " 붙여넣기 계단현상 없애기
set shiftwidth=4 " 자동 들여쓰기 너비 설정
set showmatch " 일치하는 괄호 하이라이팅
set smartcase " 검색시 대소문자 구별
set smarttab
"set smartindednt
set softtabstop=4
set tabstop=4
set ruler " 현재 커서 위치 표시
set incsearch
set statusline=\ %<%l:%v\ [%P]%=%a\ %h%m%r\ %F\
" 마지막으로 수정된 곳에 커서를 위치함
au BufReadPost *
\ if line("'\"") > 0 && line("'\"") <= line("$") |
\ exe "norm g`\"" |
\ endif
" 파일 인코딩을 한국어로
if $LANG[0]=='k' && $LANG[1]=='o'
set fileencoding=korea
endif
" 구문 강조 사용
if has("syntax")
 syntax on
endif
" 컬러 스킴 사용
colorscheme gruvbox

" 렌더링, ligature 글꼴
if has("gui_running")
  set encoding=utf-8  

  source $VIMRUNTIME/mswin.vim
  behave mswin
  
  if has('win32')
      set keymodel=startsel
       
      " set guifont=Source\ Code\ Pro:h16:cANSI:qDEFAULT
      " set guifont=JetBrains\ Mono\ Regular:h18:cANSI:qDEFAULT
      set guifont=D2Coding:h12:cHANGEUL:qDEFAULT     
	  set renderoptions=type:directx,
                        \gamma:1.0,
                        \contrast:0.5,
                        \level:1,
                        \geom:1,
                        \renmode:5,
                        \taamode:1

      " restore Ctrl-F to Page down
      unmap <C-F>
  elseif has('gui_macvim')  
      set guifont=JetBrains\ Mono\ 16
      set antialias
  else
      set guifont=JetBrains\ Mono\ 16
  endif
  " Turn off toolbar
  set guioptions-=T
  " Turn on menu
  set guioptions+=m
end

" 한줄 주석 처리
map // :s/^/\/\/<cr>:noh<cr>
map /; :s/^\/\//<cr>:noh<cr>
" 한줄 주석 처리 /**/
"map // V:s/^/\/*/<cr>gv:s/$/*\//<cr>:noh<cr>
"map /; V:s/^\/\*//<cr>gv:s/\*\/$/<cr>:noh<cr>
" 여러줄 주석 처리 /**/
"vmap // :s/^/\/*/<cr>gv:s/$/*\//<cr>:noh<cr>
"vmap /; :s/^\/\*//<cr>gv:s/\*\/$/<cr>:noh<cr>