CC      = g++
CFLAGS  = -std=gnu++17 -Wall -Wextra -Wno-unknown-pragmas -O2 -I/opt/boost/gcc/include -I/opt/ac-library
LDFLAGS = -L/opt/boost/gcc/lib
LIBS    =
DEBUG   =
OBJS    = ./main.o
PROGRAM = ./a.out

.PHONY: all
all:		compare-score

.PHONY: compile
compile:	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)
	@echo "Compile done."

%.o:		%.cpp
	@echo Compiling...
	@$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<


TOOL_DIR = ./tools

IN_DIR   = $(TOOL_DIR)
IN_FILES = $(wildcard $(IN_DIR)/input_*.txt)
TEST_IN  = $(firstword $(IN_FILES))

.PHONY: test
test:	$(PROGRAM)
	time -p $(PROGRAM) <$(TEST_IN)


OUT_DIR        = ./out
OUT_FILES      = $(addprefix $(OUT_DIR)/,$(patsubst $(IN_DIR)/input_%,%,$(IN_FILES)))
ERR_DIR        = ./err
ERR_FILES      = $(addprefix $(ERR_DIR)/,$(patsubst $(IN_DIR)/input_%,%,$(IN_FILES)))
SCORE_FILE     = ./scores.csv
OLD_SCORE_FILE = ./_scores.csv

.PHONY: bench
bench:	$(SCORE_FILE)

compare-score:	$(SCORE_FILE)
	@if [ -f $(OLD_SCORE_FILE) ]; then\
		bash bin/diff-score.bash $(OLD_SCORE_FILE) $(SCORE_FILE) ; \
	fi

SCORE_CALCULATOR_BIN = python3 $(TOOL_DIR)/judge.py
$(SCORE_FILE):	$(OUT_FILES)
	@echo
	@echo 'seed,score,real,user,sys,' >$@
	@for err_file in $$(echo "$(ERR_FILES)" | tr " " "\n" | sort | tr "\n" " "); do \
		basename="$$(basename $$err_file)" ; \
		\
		sed -i "s|Score = .*||g" $$err_file ; \
		echo -n "Score = " >>$$err_file ; \
		$(SCORE_CALCULATOR_BIN) $(IN_DIR)/input_$$basename $(OUT_DIR)/$$basename \
			| sed "s|score:||" >>$$err_file ; \
		\
		echo $$err_file | xargs -I{} sh -ec ' \
			echo -n "{}," | sed "s|.*/\([0-9]\+\)\.txt|\1|" ; \
			grep -e "^Score = " {} | sed "s/^Score = \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^real " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^user " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^sys " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			echo \
		' >>$@ ; \
	done

$(OUT_DIR)/%.txt:	$(IN_DIR)/input_%.txt $(PROGRAM) $(OUT_DIR) $(ERR_DIR)
	@echo -n "$* "
	@rm -f $(ERR_DIR)/$(notdir $@)
	@time -p $(PROGRAM) <$< >$@ 2>$(ERR_DIR)/$(notdir $@)

$(OUT_DIR) $(ERR_DIR):
	@mkdir -p $@


.PHONY: clean
clean:
	@rm -rf *.o *~ $(OUT_DIR)/* $(ERR_DIR)/*
