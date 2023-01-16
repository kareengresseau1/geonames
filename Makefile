build: compile
	

compile: geonames.c
	gcc -o geonames -std=c11 geonames.c	

test: build database 
	bats check.bats

database: 
	curl -L http://download.geonames.org/export/dump/countryInfo.txt -o countryInfo.txt
	curl -L http://download.geonames.org/export/dump/cities15000.zip -o cities15000.zip
	unzip cities15000.zip 
html:
	pandoc -o README.html -sc pandoc.css README.md
	pandoc -o sujet,html -sc pandoc.css sujet.md 


clean:
	rm countryInfo.txt
	rm cities15000.txt
	rm -rf cities15000.zip
	rm -f *.o
	rm -f *.html
