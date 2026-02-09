# Detect architecture
!IF "$(PROCESSOR_ARCHITECTURE)" == "AMD64"
ARCH=x86_64
!ELSE IF "$(PROCESSOR_ARCHITECTURE)" == "ARM64"
ARCH=arm64
!ELSE
ARCH=x86_64
!ENDIF

APP_SRC=NoiseBackendExample
RKT_SRC=core

RESOURCES_PATH=$(APP_SRC)\res
RUNTIME_NAME=runtime-$(ARCH)
RUNTIME_PATH=$(RESOURCES_PATH)\$(RUNTIME_NAME)

all: $(RESOURCES_PATH)\core-$(ARCH).zo

clean:
	if exist $(RESOURCES_PATH) rmdir /s /q $(RESOURCES_PATH)

$(RESOURCES_PATH)\core-$(ARCH).zo: $(RKT_SRC)\*.rkt
	if not exist $(RESOURCES_PATH) mkdir $(RESOURCES_PATH)
	if exist $(RUNTIME_PATH) rmdir /s /q $(RUNTIME_PATH)
	raco ctool --runtime $(RUNTIME_PATH) --runtime-access $(RUNTIME_NAME) --mods $@ $(RKT_SRC)\main.rkt
