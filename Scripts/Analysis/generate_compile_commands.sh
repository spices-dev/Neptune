#!/bin/bash
# @file generate_compile_commands.sh
# @brief Generate compile_commands.json for all subprojects
# @author Spices.

# Exit on error
set -e

# To root directory
cd "../../"

# Color Output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Usage
usage() {
    echo "Usage: $0 [--platform <windows|emscripten>] [--output <filename>]"
    echo ""
    echo "Options:"
    echo "  --platform <name>   windows emscripten "
    echo "  --output <filename> (Default: compile_commands_<platform>.json)"
    echo "  --help              "
    exit 1
}

# Default Value
PLATFORM="windows"
OUTPUT_FILE=""

# Parse Args
while [[ $# -gt 0 ]]; do
    case $1 in
        --platform)
            PLATFORM="$2"
            shift 2
            ;;
        --output)
            OUTPUT_FILE="$2"
            shift 2
            ;;
        --help)
            usage
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            usage
            ;;
    esac
done

# Define Output files
if [ -z "$OUTPUT_FILE" ]; then
    OUTPUT_FILE="compile_commands_${PLATFORM}.json"
fi

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}Generating compile_commands.json${NC}"
echo -e "${GREEN}  Platform: ${PLATFORM}${NC}"
echo -e "${GREEN}  Output:   ${OUTPUT_FILE}${NC}"
echo -e "${GREEN}========================================${NC}"

# Defines projects
SUBDIRS="Runtime UnitTest Neptune Editor"

# Temp file
JSON_FILES=""

# Iter projects
for dir in $SUBDIRS; do
    if [ -f "$dir/Makefile" ]; then
        echo -e "${YELLOW}Generating for $dir...${NC}"
        
        cd "$dir"

        # generate compile_commands
        set +e
        make -n -k 2>/dev/null | compiledb -o "../compile_commands_${dir}_${PLATFORM}.json"
        # this report link error
        #compiledb -o "../compile_commands_${dir}_${PLATFORM}.json" make -n -k
        set -e
        
        cd ..
        
        # Check
        if [ -f "compile_commands_${dir}_${PLATFORM}.json" ]; then
            ENTRY_COUNT=$(jq '. | length' "compile_commands_${dir}_${PLATFORM}.json")
            echo -e "${GREEN}  ✓ ${dir} done (${ENTRY_COUNT} entries)${NC}"
            JSON_FILES="$JSON_FILES compile_commands_${dir}_${PLATFORM}.json"
            echo -e "${GREEN}  ✓ ${dir} done${NC}"
        else
            echo -e "${RED}  ✗ ${dir} failed (file not found)${NC}"
        fi
    else
        echo -e "${YELLOW}  ⚠ ${dir} skipped (no Makefile)${NC}"
    fi
done

# Check
if [ -z "$JSON_FILES" ]; then
    echo -e "${RED}Error: No compile_commands JSON files generated!${NC}"
    exit 1
fi

# Merge
echo -e "${YELLOW}Merging JSON files...${NC}"
jq -s 'add' $JSON_FILES > "$OUTPUT_FILE"

# Statictics
ENTRY_COUNT=$(jq '. | length' "$OUTPUT_FILE")
echo -e "${GREEN}✓ Merged ${ENTRY_COUNT} entries into ${OUTPUT_FILE}${NC}"

# Clean
echo -e "${YELLOW}Cleaning up temporary files...${NC}"
rm -f $JSON_FILES

# Done
echo -e "${GREEN}Done!${NC}"