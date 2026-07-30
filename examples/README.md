# Generate and validate a test vector
1. Open a terminal and run the following:
   ```bash
   time dd if=/dev/random of=random_file.bin bs=1 count=4096
   ```
2. Run the statistical entropy validator.
   ```bash
   ./entropy_validator random_file.bin
   ```
3. Try again, adjusting the byte and block sizes, as well as the output file, until you are happy with the results.