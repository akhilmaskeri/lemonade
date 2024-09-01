# game: 
# 	g++ -o game game.cpp -lncurses
# clean:
# 	rm -f a.out game

build:
	@if [ -z "$(REPO)" ]; then \
		echo "Usage: make build REPO=<folder_name>"; \
		exit 1; \
	fi
	@echo "Building $(REPO)..."
	@if [ -d "$(REPO)" ]; then \
		cd $(REPO) && make build; \
	else \
		echo "Repository $(REPO) not found"; \
		exit 1; \
	fi

run:
	@if [ -z "$(REPO)" ]; then \
		echo "Usage: make build REPO=<folder_name>"; \
		exit 1; \
	fi
	@echo "Running $(REPO)..."
	@if [ -d "$(REPO)" ]; then \
		cd $(REPO) && make run; \
	else \
		echo "Repository $(REPO) not found"; \
		exit 1; \
	fi
