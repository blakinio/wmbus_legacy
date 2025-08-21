import esphome.config_validation as cv


def my_key(value):
    value = cv.string_strict(value)
    parts = [value[i : i + 2] for i in range(0, len(value), 2)]
    if (len(parts) != 16) and (len(parts) != 0):
        raise cv.Invalid("Key must consist of 16 hexadecimal numbers")
    parts_int = []
    if any(len(part) != 2 for part in parts):
        raise cv.Invalid("Key must be format XX")
    for part in parts:
        try:
            parts_int.append(int(part, 16))
        except ValueError:
            # pylint: disable=raise-missing-from
            raise cv.Invalid("Key must be hex values from 00 to FF")
    return "".join(f"{part:02X}" for part in parts_int)
