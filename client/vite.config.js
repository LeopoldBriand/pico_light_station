import { defineConfig } from 'vite';
import { viteSingleFile } from 'vite-plugin-singlefile';

export default defineConfig({
  plugins: [viteSingleFile()],
  build: {
    // Minify output aggressively
    minify: 'terser', 
    terserOptions: {
      compress: {
        drop_console: false,
      }
    }
  }
});
