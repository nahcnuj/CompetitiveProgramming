CC      = g++
CFLAGS  = -std=gnu++17 -Wall -Wextra -O2 -DONLINE_JUDGE -I/opt/boost/gcc/include -I/opt/ac-library
LDFLAGS = -L/opt/boost/gcc/lib
LIBS    =
OBJS    = ./main.o
PROGRAM = ./a.out

all:		compile benchmark compare-score

compile:	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

%.o:		%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o *~ $(PROGRAM)


TESTER_DIR = ./tools
TESTER_BIN = $(TESTER_DIR)/target/release/tester
IN_DIR     = $(TESTER_DIR)/in
IN_FILES   = $(wildcard $(IN_DIR)/*.txt)
TEST_IN    = $(firstword $(IN_FILES))

test:	$(PROGRAM)
	time -p $(TESTER_BIN) $(TEST_IN) $(PROGRAM)


OUT_DIR        = ./out
OUT_FILES      = $(addprefix $(OUT_DIR)/,$(patsubst $(IN_DIR)/%.txt,%.txt,$(IN_FILES)))
ERR_DIR        = ./err
ERR_FILES      = $(addprefix $(ERR_DIR)/,$(patsubst $(IN_DIR)/%.txt,%.txt,$(IN_FILES)))
SCORE_FILE     = ./scores.csv
OLD_SCORE_FILE = ./_scores.csv

benchmark:
	@$(MAKE) --no-print-directory pre-benchmark
	@$(MAKE) --no-print-directory run-benchmark

pre-benchmark:
	@rm -rf $(OUT_DIR)/* $(ERR_DIR)/*

run-benchmark:	$(PROGRAM) $(OUT_FILES)

compare-score:	$(SCORE_FILE)
	@[ -f $(OLD_SCORE_FILE) ] && bash bin/diff-score.bash $(OLD_SCORE_FILE) $(SCORE_FILE)

$(SCORE_FILE):
	@echo 'seed,score,real,user,sys,' >$@
	@echo $(ERR_FILES) | tr ' ' "\n" | sort \
		| xargs -n1 -I{} sh -c '\
			echo -n $$(echo {} | sed "s|.*/0\+\([0-9]\+\)\.txt|\1|"),;\
			grep -e "^Score = " {} | sed "s/^Score = \(.*\)$$/\1,/" | tr -d "\n";\
			grep -e "^real " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n";\
			grep -e "^user " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n";\
			grep -e "^sys " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n";\
			echo' >>$@

$(OUT_DIR)/%.txt:	$(IN_DIR)/%.txt $(PROGRAM) $(OUT_DIR) $(ERR_DIR)
	time -p $(TESTER_BIN) $< $(PROGRAM) >$@ 2>$(ERR_DIR)/$$(basename $@)

$(OUT_DIR) $(ERR_DIR):
	@mkdir -p $@
