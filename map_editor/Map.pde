class Vector2 {
        public char x;
        public char y;
}

class Vector2i {
        public int x;
        public int y;
}

class Vector2f {
        public float x;
        public float y;
}

class Map {
        private byte[]  _objects;
        private char    _tileSize;
        private String  _tileMap = "";
        private short[] _links = new short[4];
        private Vector2 _size = new Vector2();
        private Vector2i _camPos = new Vector2i();

        Map(String path)
        {
                try {
                        InputStream fileReader = new FileInputStream(new File(path));
                        int b = 0;

                        do {
                                b = fileReader.read();
                                if (b > 0)
                                        this._tileMap += (char)b;
                        } while (b > 0);

                        if (b == -1) {
                                fileReader.close();
                                throw new IOException("EOF reached (Tilemap)");
                        }

                        b = fileReader.read();
                        if (b == -1) {
                                fileReader.close();
                                throw new IOException("EOF reached (Tile size)");
                        }
                        this._tileSize = (char)b;

                        b = fileReader.read();
                        if (b == -1) {
                                fileReader.close();
                                throw new IOException("EOF reached (Size x)");
                        }
                        this._size.x = (char)b;

                        b = fileReader.read();
                        if (b == -1) {
                                fileReader.close();
                                throw new IOException("EOF reached (Size y)");
                        }
                        this._size.y = (char)b;

                        for (int i = 0; i < this._links.length; i++) {
                                this._links[i] = 0;
                                for (int j = 0; j < 2; j++) {
                                        b = fileReader.read();
                                        if (b == -1) {
                                                fileReader.close();
                                                throw new IOException("EOF reached (Link " + i + ")");
                                        }
                                        this._links[i] <<= 8;
                                        this._links[i] |= (char)b;
                                }
                        }

                        this._objects = new byte[this._size.x * this._size.y];
                        b = fileReader.read(this._objects);
                        if (b == -1) {
                                fileReader.close();
                                throw new IOException("EOF reached (Objects)");
                        }

                        fileReader.close();
                } catch (Exception e) {
                        StringWriter writer = new StringWriter();
                        PrintWriter printWriter = new PrintWriter(writer);

                        e.printStackTrace(printWriter);
                        printWriter.flush();

                        error("Cannot load file " + path + ":\n" + writer.toString());
                }
        }

        private float _updateCameraCenter(float size, float screenSize, float focusPoint)
        {
                if (size <= screenSize)
                        return size / 2;

                if (focusPoint < screenSize / 2)
                        return screenSize / 2;

                if (focusPoint > size - screenSize / 2)
                        return size - screenSize / 2;

                return focusPoint;
        }

        private Vector2f _updateCameraPosition()
        {
                Vector2f pos = new Vector2f();
                
                pos.x = this._updateCameraCenter(this._size.x * this._tileSize, width, this._camPos.x);
                pos.y = this._updateCameraCenter(this._size.y * this._tileSize, height, this._camPos.y);
                return pos;
        }

        public void render()
        {
                Vector2f pos = this._updateCameraPosition();
                Vector2i size = new Vector2i();

                size.x = width;
                size.y = height;
                pos.x -= width / 2.;
                pos.y -= height / 2.;
                pos.x /= this._tileSize;
                pos.y /= this._tileSize;
                size.x = ceil(width / (float)this._tileSize);
                size.y = ceil(height / (float)this._tileSize);

                for (int y = pos.y < 0 ? 0 : (int)pos.y; y < pos.y + size.y && y < this._size.y; y++) {
                        for (int x = pos.x < 0 ? 0 : (int)pos.x; x < pos.x + size.x && x < this._size.x; x++) {
                                if ((this._objects[x + y * this._size.x] & 0x80) != 0)
                                        tint(255, 200, 200);
                                else
                                        tint(255);
                                image(
                                        sprites.get(this._tileMap).get(
                                                (this._objects[x + y * this._size.x] & 0x7F) * this._tileSize,
                                                0,
                                                this._tileSize,
                                                this._tileSize
                                        ),
                                        (x - pos.x) * this._tileSize,
                                        (y - pos.y) * this._tileSize
                                );
                        }
                }
        }
}
