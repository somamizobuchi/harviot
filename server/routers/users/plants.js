const router = require('express').Router()
const mongoose = require('mongoose')
const Plant = require('../../models/Plant')
const User = require('../../models/User')
const {auth, verifyRole, ROLES} = require('../auth')

router.get('/', auth, async (req, res) => {
    try {
        let user = await User.findById(res.locals._id).select('plants').exec()
        if(!user.plants || user.plants.length == 0) return res.sendStatus(204)
        let plants = await Plant.find()
            .where('_id')
            .in(user.plants)
            .select(['name', 'info'])
            .exec()
        return res.status(200).json(plants)
    } catch (e) {
        res.sendStatus(500)
    }
})

router.post('/', auth, verifyRole(ROLES.admin), async (req, res) => {
    if(!req.query.user_id || !req.query.plant_id)
        return res.sendStatus(422)
    try {
        if(!(await User.findById(req.query.user_id))) 
            return res.sendStatus(404)
        if(!(await Plant.findById(req.query.plant_id)))
            return res.sendStatus(404)
        await User.findByIdAndUpdate(req.query.user_id, {
            $addToSet: { plants: mongoose.Types.ObjectId(req.query.plant_id) }
        }).exec()

        return res.sendStatus(200)

    } catch (e) {
        console.log(e)
        return res.sendStatus(500)
    }
})

module.exports = router