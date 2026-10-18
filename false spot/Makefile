ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif

ELF := bgm_test.elf
CFLAGS := -Wall
LDADD := -lSceAudioOut -lSceUserService -lm

all: $(ELF)

$(ELF): main.c
	$(CC) $(CFLAGS) $^ $(LDADD) -o $@

clean:
	rm -f $(ELF)

test: $(ELF)
	$(PS5_DEPLOY) -h $(PS5_HOST) -p $(PS5_PORT) $^
