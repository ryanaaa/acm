set number
set nocompatible

filetype on
filetype indent on
filetype plugin on

" tabstop noexpandtab shiftwidth softtabstop
set ts=4
set noet 
set sw=4
set sts=4

map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l

" 错误替换
abbr Include include

set fileencodings=utf-8,gb18030,gbk,gb2312,cp936

map <F2> gg"+yG
map <F3> "+p
