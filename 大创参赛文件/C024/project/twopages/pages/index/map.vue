<template>
	<view class="">
		<map :markers="covers" :longitude="longitude" :latitude="latitude" style="width: 100%; height: 93vh;">
		</map>
		<view class="Control">
			<view class="btn" @click="saveInfo">签到</view>
		</view>
	</view>

</template>

<script>
	export default {
		data() {
			return {
				longitude: '',
				latitude: '',
				covers: []
			}
		},
		onLoad() {
			this.getList()
			this.getLocation()
		},
		methods: {
			getLocation() {
				let _this = this;
				uni.getLocation({
					type: 'gcj02',
					success: function(res) {
						console.log(res, '123')
						_this.latitude = res.latitude
						_this.longitude = res.longitude
						_this.covers.push({
							id: 0,
							latitude: res.latitude,
							longitude: res.longitude,
							width: 30,
							height: 30,

						})
					}
				});
			},
			saveInfo() {
				let _this = this
				let longitude = this.longitude
				let latitude = this.latitude
				uni.request({
					url: 'http://192.168.31.54/Index/saveInfo',
					method: "POST",
					data: {
						longitude,
						latitude
					},
					success(res) {
						_this.getList()
						uni.showToast({
							title: 'Sign successful',
							duration: 1000
						});
						setTimeout(() => {
							uni.navigateBack(1)
						}, 1500)
						console.log(res);
					}
				})
			},
			getList() {
				let _this = this
				uni.request({
					url: 'http://192.168.31.54/Index/getList',
					method: "GET",
					success(res) {
						console.log(res);
						res.data.data.map(item => {
							_this.covers.push({
								id: item.id,
								latitude: item.latitude,
								longitude: item.longitude,
								width: 30,
								height: 30,

							})
						})

					}
				})
			}

		}
	}
</script>

<style lang="scss">
	.Control {
		width: 100%;
		background-color: #FFF;
		position: fixed;
		bottom: 0;
		border-top-left-radius: 25rpx;
		border-top-right-radius: 25rpx;

		.btn {
			background-color: #3392ea;
			margin: 100rpx auto;
			width: 90%;
			color: #efefef;
			text-align: center;
			border-radius: 40rpx;
			padding: 25rpx 0;
		}
	}
</style>
