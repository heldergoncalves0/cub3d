from PIL import Image

# Convert the 'N' image to JPEG
n_image_path = "W.webp"
n_image = Image.open(n_image_path)

# Convert to JPEG and save
n_jpeg_path = "W.jpg"
n_image.convert("RGB").save(n_jpeg_path, "JPEG")

n_jpeg_path
