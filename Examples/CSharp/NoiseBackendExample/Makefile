all: core.zo

core.zo: core/main.rkt
	raco ctool --mods core.zo core\main.rkt
	if not exist NoiseBackendExample\res mkdir NoiseBackendExample\res
	copy core.zo NoiseBackendExample\res\

clean:
	if exist core.zo del core.zo
	if exist NoiseBackendExample\res\core.zo del NoiseBackendExample\res\core.zo
	if exist NoiseBackendExample\res rmdir NoiseBackendExample\res
