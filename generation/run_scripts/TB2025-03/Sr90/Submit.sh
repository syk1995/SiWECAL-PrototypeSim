#!/bin/bash

SOURCE_SCRIPT="produce_detailled.sh"
TARGET_DIR="./submit_scripts"
job_begin=1
job_end=10

if [ -d "$TARGET_DIR" ]; then
    rm -rf "$TARGET_DIR"
fi
mkdir -p "$TARGET_DIR"

for i in $(seq $job_begin $job_end); do
    TARGET_SCRIPT="$TARGET_DIR/produce_detailled_$i.sh"
    cp "$SOURCE_SCRIPT" "$TARGET_SCRIPT"

    sed -i "s|outputFile=\$PROD_NAME/\$PARTICLE_TYPE.edm4hep.root|outputFile=\$PROD_NAME/\${PARTICLE_TYPE}_$i.edm4hep.root|g" "$TARGET_SCRIPT"
    sed -i "s|--random.seed 1|--random.seed $i|g" "$TARGET_SCRIPT"
done

cd $TARGET_DIR
for i in $(seq $job_begin $job_end); do
    t3submit_el9 -short produce_detailled_$i.sh
done
cd ..
