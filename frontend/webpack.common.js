const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
	entry: './src/index.tsx',
	module: {
		rules: [
			{
				test: /\.(js)$/,
				exclude: /node_modules/,
				use: ['babel-loader']
			},
			{
				test: /\.tsx?$/,
				use: 'ts-loader',
				exclude: /node_modules/,
			},
			{
				test: /\.html$/,
				use: ['html-loader']
			},
			{
				test: /\.(png|jpe?g|gif|svg|ico)$/i,
				loader: 'file-loader',
				options: {
					name: 'img/[name].[ext]'
				}
			}
		]
	},
	resolve: {
		extensions: ['.tsx', '.ts', '.js'],
	},
	plugins: [
		new HtmlWebpackPlugin({
			template: './public/index.html'
		})
	]
}