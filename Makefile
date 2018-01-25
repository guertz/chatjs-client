# Target application to be compiled
TARGET=application

# Directory containing the source files + js pages components
DIR_SRC=src
# Directory containing common assets files: index.html, css, js framework
DIR_ASSETS=assets
# Directory where to put binary translated resources (common assets files)
DIR_ASSETS_SRC=$(DIR_SRC)/.assets

# Directory containing the built application (could be debug or release)
DIR_BUILD_SPACE=.build

# Assets needed by the app to work
#	1° line are the translated files from DIR_ASSETS
#	2° line are app components connected to a .cc page or component
#
# Both has to be manually updated: see helpers at bottom
ASSETS=	$(DIR_ASSETS_SRC)/index.html.o $(DIR_ASSETS_SRC)/appinit.js.o $(DIR_ASSETS_SRC)/style.css.o $(DIR_ASSETS_SRC)/stylew3.css.o \
		src/app/app.ojs src/directives/modals/auth-modal/auth-modal.ojs src/directives/modals/chat-modal/chat-modal.ojs src/directives/navbar/navbar.ojs src/directives/navbar/profile/profile.ojs src/directives/toast/toast.ojs src/directives/modals/modals.ojs src/pages/chat-details/chat-details.ojs src/pages/chat-list/chat-list.ojs

# Compiled parts that compose the whole app
APP=src/app/app.o src/common/base64/base64.o src/common/helpers/helpers.o src/common/logger/logger.o src/common/web-ui/web-ui.o src/directives/modals/auth-modal/auth-modal.o src/directives/modals/chat-modal/chat-modal.o src/directives/modals/connectivity/connectivity.o src/directives/modals/modals.o src/directives/navbar/navbar.o src/directives/navbar/profile/profile.o src/directives/toast/toast.o src/main.o src/pages/chat-details/chat-details.o src/pages/chat-list/chat-list.o src/protocol/sockets/definitions/request.o src/protocol/sockets/definitions/response.o src/protocol/sockets/easywsclient.o src/protocol/sockets/wscustom.o src/states/auth-state/auth-state.o src/states/auth-state/definitions/auth.o src/states/auth-state/definitions/request.o src/states/auth-state/definitions/response.o src/states/auth-state/definitions/user.o src/states/chat-state/chat-state.o src/states/users-state/definitions/request.o src/states/users-state/definitions/response.o src/states/users-state/definitions/stream.o src/states/users-state/users-state.o

# Flags that will be added to CXXFLAGS for the release build stage
RELEASE_FLAGS= -DNDEBUG
# Flags that will be added to CXXFLAGS for the debug build stage
DEBUG_FLAGS= -g -DDEBUG_MODE -Wall -Wextra -pedantic

# BUILD_FLAGS are setted to RELEASE_FLAGS by default
BUILD_FLAGS=$(DEBUG_FLAGS)

# Debug is enabled by default
# 	for release: ENV=release
ifeq ($(ENV),release)
	# Overwriting build flags with RELEASE_FLAGS
	BUILD_FLAGS=$(RELEASE_FLAGS)
	ENV=release
else	
	ENV=debug
endif

# Specifying compiler
CXX=g++
# List of compiler flags for all the specified parts of the app
# 	Here using -isystem to prevent showing included dependencies Warnings
CXXFLAGS= $(BUILD_FLAGS) -std=c++11 -I$(DIR_SRC) -isystem./dependencies/webview -isystem./dependencies/json $(WEBVIEW_CFLAGS)

# Linker flags
LDFLAGS += -lpthread

TARGET_OS ?= $(OS)
ifeq ($(TARGET_OS),Windows_NT)
	TARGET=application.exe
	WEBVIEW_CFLAGS := -DWEBVIEW_WINAPI=1
	WEBVIEW_LDFLAGS := -lole32 -lcomctl32 -loleaut32 -luuid -mwindows
	# Adding linker flah lws2_32 for window platforms
	# needed by sockets
	LDFLAGS += -lws2_32
else ifeq ($(shell uname -s),Linux)
	WEBVIEW_CFLAGS := -DWEBVIEW_GTK=1 $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.0)
	WEBVIEW_LDFLAGS := $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.0)
else ifeq ($(shell uname -s),Darwin)
	WEBVIEW_CFLAGS := -DWEBVIEW_COCOA=1 -x objective-c
	WEBVIEW_LDFLAGS := -framework Cocoa -framework WebKit
endif

# ----------------- #
# ----  BUILD  ---- #
# ---- HELPERS ---- #
# ----------------- #
.PHONY: build clean-env init directories assets depend check-env refresh-app refresh-all refresh-assets

# Example: run commands as following
# *this is more safe then running default target make
#  TODO: i can still reduce the steps (kind of unify them)
#  		 default mean release or debug
#  TODO: always check on the ofile app/assets list definition
#		 on top
#
#	Debug: || ENV=debug
# 		make depend
#		make
#	________
#	Release:
#		make ENV=release depend
#		make ENV=release
#
# --------------------

# FIRST TARGET: ORDER MATTER
# What if up to date?
#
# Build the application based on the target definition.
# *It will first check the environment
# *It will both refresh APP & ASSETS file changes
#
# Parent phony targets:
#	TARGET (default: application)
#
# Condition: environment has to be ready (see depend)
build: check-env $(TARGET)

# Command to test if the env is clean
# *No app version (debug || release) are yet selected
# *Make process will stop if it fails otherwhise it will
#  simply print desired env version
#
# Condition: run on new build after cleanall
clean-env:
	test -e $(DIR_BUILD_SPACE)/debug 	 && exit 1 || echo "Clean step 1";
	test -e $(DIR_BUILD_SPACE)/release	 && exit 1 || echo "Clean step 2";
	test -e $(DIR_BUILD_SPACE)/$(TARGET) && exit 1 || echo "Clean step 3";	

# Command to init the current workspace with the desired 
# env version.
# It will simply touch a file situated in the DIR_BUILD_SPACE
# named as the current env version
#
# Parent phony targets:
#	clean-env (see also for condition)
init: clean-env
	touch $(DIR_BUILD_SPACE)/$(ENV)

# Creates the .build directory if doesn't exist
directories:
	mkdir -p $(DIR_BUILD_SPACE)

# Translating common assets files
assets:
	test -d $(DIR_ASSETS_SRC) || mkdir -p $(DIR_ASSETS_SRC)
	ld -r -b binary -o $(DIR_ASSETS_SRC)/appinit.js.o   $(DIR_ASSETS)/appinit.js
	ld -r -b binary -o $(DIR_ASSETS_SRC)/index.html.o   $(DIR_ASSETS)/index.html
	ld -r -b binary -o $(DIR_ASSETS_SRC)/style.css.o    $(DIR_ASSETS)/style.css
	ld -r -b binary -o $(DIR_ASSETS_SRC)/stylew3.css.o  $(DIR_ASSETS)/stylew3.css

# Prepare application for build step
# It generates the dependencies of the source files passed as a argument
#
# Parent phony targets:
#	directories
# 	init
#	assets
depend: directories init assets
	g++ -I$(DIR_SRC) -std=c++11 -MM $(shell find $(DIR_SRC) -name "*.cc" $(NOPATH)) > depends

# Command to test if the user is compiling the app for
# the right version.
# *if the user is trying to build an app version (debug || release)
#  different for the current one in workspace it will fail
# *Prevents mixed build status
#
# Condition: run after depend
#  (otherwise no directory and env data)
# TODO: also check depend?
check-env:
	test -e $(DIR_BUILD_SPACE)/$(ENV) || exit 1;

# Build the application based on the target definition.
# *It will clean and recompile all APP objects
# *Also use when changing env.h
# 
# Parent phony targets:
#	clean
#	build (see for advice)
refresh-app: clean build

# Build the application based on the target definition.
# *It will refresh assets translated in depend step
# 
# Parent phony targets:
#	assets
#	build (see for advice)
refresh-assets: assets build

# Build the application based on the target definition.
# *It will clean and recompile all APP objects
# *It will refresh assets translated in depend step
# 
# Parent phony targets:
#	assets
#	refresh-app
refresh-all: assets refresh-app
	
# ----------------- #
# ----  CLEAN  ---- #
# ---- HELPERS ---- #
# ----------------- #
.PHONY: clean clean-assets cleanall

# Cleaning compiled parts of the app
# *Excluding translated common assets
clean: 
	rm -rf $(shell find $(DIR_SRC) -name "*.o" -not -path "$(DIR_ASSETS_SRC)/*")

# Cleaning translated resources of the app
# *Excluding translated common assets
clean-assets:
	rm -rf $(shell find $(DIR_SRC) -name "*.ojs" -not -path "$(DIR_ASSETS_SRC)/*")

# Cleaning everything up
#
# Parent phony targets:
#	clean
#	clean-assets
cleanall: clean clean-assets
	rm -f depends
	rm -rf $(DIR_BUILD_SPACE)
	rm -rf $(DIR_ASSETS_SRC)

# ----------------------- #
# ---- APP PARTS LIST --- #
# ----     HELPERS    --- #
# ----------------------- #
.PHONY: assets-files app-files

# Display the list of translated assets file that compose the app
# *see ASSETS
# *list of translated/to translate files used as requirements (copy & paste is fine)
assets-files:
	find $(DIR_SRC) -name "*.js" $(NOPATH) | sed -e "s/.js/.ojs/g" | tr '\n' ' '

# Display the list of compiled object files that will compose the app
# *see APP
# *list of compiled/to compile files used as requirements (copy & paste is fine)
app-files: 
	find $(DIR_SRC) -name "*.cc" $(NOPATH) | sed -e "s/.cc/.o/g" | tr '\n' ' '

# ----------------------- #
# -------- BUILD -------- #
# ----------------------- #
-include depends

.PHONY: $(TARGET)

# TARGET rule
# *Depend on current OS
# *Invoked by build that will also check the env
$(TARGET): $(ASSETS) $(APP)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(WEBVIEW_LDFLAGS) -o $(DIR_BUILD_SPACE)/$@

# Omitted rule for compiling each dependencies as a object file
# ... Using CXX & CXXFLAGS
#	  Optimize to bundle assets to compiled .o component

# Rule for translating each js file in a binary format
%.ojs: %.js
	ld -r -b binary -o $@ $<