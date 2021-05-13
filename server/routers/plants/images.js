const mongoose = require('mongoose')
const Log = require('../../models/Log')
const Plant = require('../../models/Plant')
const User = require('../../models/User')
const { auth, verifyRole, ROLES } = require('../auth')
const router = require('express').Router()
const multer = require('multer')
const aws = require('aws-sdk')

// MULTER
var storage = multer.memoryStorage()
var upload = multer({storage: storage})


router.post('/', upload.single('imageFile'), (req, res) => {

    if(!req.file) return res.sendStatus(422)

    aws.config.credentials = {
        accessKeyId: process.env.AWS_ACCESS_KEY_ID,
        secretAccessKey: process.env.AWS_SECRET_KEY
    }
    
    var s3 = new aws.S3({
        region: process.env.S3_BUCKET_REGION
    })

    var params = {
        Bucket: process.env.S3_BUCKET_NAME,
        Body: req.file.buffer,
        ContentType: req.file.mimetype,
        ContentEncoding: 'base64',
        ACL: 'public-read',
        Key: req.file.originalname
    }

    s3.upload(params, async (err, data) => {
        if (err) {
            console.log(err)
            res.sendStatus(500)
        }
    })
    
    res.sendStatus(200)
})


module.exports = router
