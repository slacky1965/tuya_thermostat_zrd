import struct
import sys

def read_ota_header(filepath):
    with open(filepath, 'rb') as f:
        data = f.read(69)  # minimum header size

        tag = struct.unpack('<I', data[0:4])[0]
        if tag != 0x0BEEF11E:
            print(f"Not a valid Zigbee OTA file (tag: 0x{tag:08X})")
            return

        header_version = struct.unpack('<H', data[4:6])[0]
        header_length = struct.unpack('<H', data[6:8])[0]
        field_control = struct.unpack('<H', data[8:10])[0]
        manufacturer_code = struct.unpack('<H', data[10:12])[0]
        image_type = struct.unpack('<H', data[12:14])[0]
        file_version = struct.unpack('<I', data[14:18])[0]
        stack_version = struct.unpack('<H', data[18:20])[0]
        header_string = data[20:52].decode('ascii', errors='replace').rstrip('\x00')
        total_size = struct.unpack('<I', data[52:56])[0]

        print(f"OTA Tag:           0x{tag:08X}")
        print(f"Header Version:    {header_version}")
        print(f"Header Length:     {header_length}")
        print(f"Field Control:     0x{field_control:04X}")
        print(f"Manufacturer Code: {manufacturer_code} (0x{manufacturer_code:04X})")
        print(f"Image Type:        {image_type} (0x{image_type:04X})")
        print(f"File Version:      {file_version} (0x{file_version:08X})")
        print(f"Stack Version:     {stack_version}")
        print(f"Header String:     '{header_string}'")
        print(f"Total Image Size:  {total_size} bytes")

read_ota_header(sys.argv[1])