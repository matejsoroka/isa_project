DOCS_NAME = ../docs/docs
DOCS_DIR = ../docs
SRC_DIR = ../src
SERVER_BIN = isaserver
CLIENT_BIN = isaclient

all: clean docs server client
clean: docs_clean bin_clean
build: server client
runserver: server runserver

docs:
	pdflatex -output-directory=$(DOCS_DIR) $(DOCS_NAME).tex
	pdflatex -output-directory=$(DOCS_DIR) $(DOCS_NAME).tex

bin_clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)

docs_clean:
	rm -f $(DOCS_NAME).dvi $(DOCS_NAME).toc $(DOCS_NAME).log $(DOCS_NAME).fdb_latexmk docs/$(DOCS_NAME).fls $(DOCS_NAME).fdb_out $(DOCS_NAME).out $(DOCS_NAME).aux $(DOCS_NAME).ps $(DOCS_NAME).pdf

server:
	g++ -Wall -Wextra -pedantic -o $(SERVER_BIN) $(SRC_DIR)/server.cpp $(SRC_DIR)/Request.cpp $(SRC_DIR)/Response.cpp $(SRC_DIR)/Handler.cpp $(SRC_DIR)/Dashboard.cpp $(SRC_DIR)/Post.cpp $(SRC_DIR)/Board.cpp

client:
	g++ -Wall -Wextra -pedantic -o $(CLIENT_BIN) $(SRC_DIR)/client.cpp $(SRC_DIR)/Request.cpp $(SRC_DIR)/Response.cpp
