import deregress

@deregress.test
def test_triangle(test):
    test.runner \
        .executable("triangle/triangle") \
        .arg("--qaf=2") \
        .arg("--grab-frames=2") \
        .run()

    test.tester.file_should_exist("frame2.png")
    test.tester.file_hash_should_match("frame2.png")


@deregress.test
def test_write_image(test):
    test.runner \
        .executable("write_image/write_image") \
        .run()

    test.tester.file_should_exist("image.png")
    test.tester.file_hash_should_match("image.png")
