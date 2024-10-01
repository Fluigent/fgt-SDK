---
name: Bug report
about: Create a report to help us improve
title: ''
labels: bug
assignees: ''

---

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Plug '...' and '...'
2. Run script for '....'
3. See error

**Expected behavior**
A clear and concise description of what you expected to happen.

**Screenshots**
If applicable, add output logs or screenshots to help explain your problem.

**Software (please complete the following information):**
 - OS: [e.g. Windows11]
 - SDK version: [e.g. 23.0]

**Instrument(s) (please complete the following information):**
- Family: [e.g. LineUP]
- Model(s): [e.g. FlowEZ, MFCS-EZ, etc.]
- SN(s):
- Firmware version(s):

**Additional context**
Add any other context about the problem here. Ideally, try to run your script with the log verbosity set to the maximum. To do so, add this line at the top of your script (example provided for Python, adapt it to your language):
```python
fgt_set_log_verbosity(5)
```
