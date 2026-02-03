.PHONY: all
all: \
	Swift/RacketCS-ios.xcframework \
	Swift/RacketCS-macos.xcframework \
	Swift/Tests/NoiseTest/Modules/mods.zo

Swift/Lib/libracketcs-universal-macos.a:
	make -C Swift/Lib libracketcs-universal-macos.a

Swift/RacketCS-ios.xcframework: Swift/Lib/include/* Swift/Lib/libracketcs-arm64-ios.a Swift/Lib/libracketcs-arm64-iphonesimulator.a
	rm -fr $@
	xcodebuild -create-xcframework \
		-library Swift/Lib/libracketcs-arm64-iphonesimulator.a -headers Swift/Lib/include \
		-library Swift/Lib/libracketcs-arm64-ios.a -headers Swift/Lib/include \
		-output $@

Swift/RacketCS-macos.xcframework: Swift/Lib/include/* Swift/Lib/libracketcs-universal-macos.a
	rm -fr $@
	xcodebuild -create-xcframework \
		-library Swift/Lib/libracketcs-universal-macos.a \
		-headers Swift/Lib/include \
		-output $@

Swift/Tests/NoiseTest/Modules/mods.zo:
	make -C Swift/Tests/NoiseTest/Modules mods.zo

.PHONY: clean
clean:
	rm -fr Swift/*.xcframework
	make -C Swift/Lib clean
	make -C Swift/Tests/NoiseTest/Modules clean
