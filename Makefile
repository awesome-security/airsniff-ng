all:
	# To lazy to do this every time
	rm -rf src/build/*
	echo "" > commands/airplay-ng.history
	git add .
	git commit -m "Daily push"
	git push
