# Target application to be compiled
TARGET=application

# Directory containing the source files + js pages components
DIR_SRC=src

# Directory containing the built application (could be debug or release)
DIR_BUILD_SPACE=.build

# Compiled parts that compose the whole app
APP=src/app/app.o src/common/base64/base64.o src/common/logger/logger.o src/common/uuid/uuid.o src/common/web-ui/web-ui.o src/components/chat-details/chat-details.o src/components/chat-list/chat-list.o src/components/modals/auth-modal/auth-modal.o src/components/modals/chat-modal/chat-modal.o src/components/modals/conn-modal/conn-modal.o src/components/modals/modals.o src/components/navbar/navbar.o src/components/navbar/profile/profile.o src/components/toast/toast.o src/main.o src/models/chats/chats.o src/models/chats/message.o src/models/json-item.o src/models/socket/auth/auth-socket.o src/models/socket/chat/chat-socket.o src/models/socket/chats/chats-socket.o src/models/socket/socket.o src/models/socket/users/users-socket.o src/models/user/user.o src/protocol/sockets/easywsclient.o src/protocol/sockets/wscustom.o src/states/auth-state/auth-state.o src/states/chats-state/chats-state.o src/states/users-state/users-state.o

# Flags that will be added to CXXFLAGS for the release build stage
RELEASE_FLAGS= -DNDEBUG
# Flags that will be added to CXXFLAGS for the debug build stage
DEBUG_FLAGS= -g -DDEBUG_MODE -Wall -Wextra -pedantic

# Debug is enabled by default
# 	for release: ENV=release
ifeq ($(ENV),release)
	BUILD_FLAGS=$(RELEASE_FLAGS)
	ENV=release
else
	BUILD_FLAGS=$(DEBUG_FLAGS)
	ENV=debug
endif

# Local server is enabled by default
# 	for release: SERVER=remote
ifeq ($(SERVER),remote)
	BUILD_FLAGS += -DSERVER_REMOTE
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
.PHONY: build clean-env init directories depend check-env refresh-app

# Example: run commands as following
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

# Prepare application for build step
# It generates the dependencies of the source files passed as a argument
#
# Parent phony targets:
#	directories
# 	init
depend: directories init
	g++ -I$(DIR_SRC) -std=c++11 -MM $(shell find $(DIR_SRC) -name "*.cc" $(NOPATH)) > depends

# Command to test if the user is compiling the app for
# the right version.
# *if the user is trying to build an app version (debug || release)
#  different for the current one in workspace it will fail
# *Prevents mixed build status
#
# Condition: run after depend
check-env:
	test -e $(DIR_BUILD_SPACE)/$(ENV) || exit 1;

# Build the application based on the target definition.
# *It will clean and recompile all APP objects
# 
# Parent phony targets:
#	clean
#	build (see for advice)
refresh-app: clean build
	
# ----------------- #
# ----  CLEAN  ---- #
# ---- HELPERS ---- #
# ----------------- #
.PHONY: clean cleanall

# Cleaning compiled parts of the app
clean: 
	rm -rf $(shell find $(DIR_SRC) -name "*.o")

# Cleaning everything up
#
# Parent phony targets:
#	cleanì
cleanall: clean
	rm -f depends
	rm -rf $(DIR_BUILD_SPACE)

# ----------------------- #
# ---- APP PARTS LIST --- #
# ----     HELPERS    --- #
# ----------------------- #
.PHONY: app-files

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
$(TARGET): $(APP)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(WEBVIEW_LDFLAGS) -o $(DIR_BUILD_SPACE)/$@