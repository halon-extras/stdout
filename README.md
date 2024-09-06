# Stdout plugin

## Installation

Follow the [instructions](https://docs.halon.io/manual/comp_install.html#installation) in our manual to add our package repository and then run the below command.

### Ubuntu

```
apt-get install halon-extras-stdout
```

### RHEL

```
yum install halon-extras-stdout
```

## Exported functions

These functions needs to be [imported](https://docs.halon.io/hsl/structures.html#import) from the `extras://stdout` module path.

### stdout(value)

Print message to stdout.

**Params**

- value `string` - The value to print

**Returns**

The number of bytes written.

**Example**

```
import { stdout } from "extras://stdout";
echo stdout("hello\n");
```

### stderr(value)

Print message to stderr.

**Params**

- value `string` - The value to print

**Returns**

The number of bytes written.

**Example**

```
import { stderr } from "extras://stdout";
echo stderr("hello\n");
```

