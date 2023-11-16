cp main.c src/${1}.c
git add *
git commit -m '${1} solved'
git push origin master
